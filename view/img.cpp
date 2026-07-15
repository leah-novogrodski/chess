#include "img.hpp"
#include <iostream>
#include <stdexcept>

static std::filesystem::path resolveImagePath(const std::string& path) {
    std::filesystem::path p(path);
    if (std::filesystem::exists(p)) return p;

    if (p.is_absolute()) return p;

    std::filesystem::path cwd = std::filesystem::current_path();
    std::filesystem::path absolutePath = std::filesystem::absolute(p);
    if (std::filesystem::exists(absolutePath)) return absolutePath;

    std::filesystem::path dir = cwd;
    for (int i = 0; i <= 4; ++i) {
        std::filesystem::path candidate = dir / p;
        if (std::filesystem::exists(candidate)) return std::filesystem::weakly_canonical(candidate);
        if (dir.has_parent_path()) dir = dir.parent_path();
        else break;
    }

    return p;
}

Img::Img() {
    // Constructor - img is automatically initialized as empty
}

Img& Img::read(const std::string& path,
               const std::pair<int, int>& size,
               bool keep_aspect,
               int interpolation) {
    std::filesystem::path resolvedPath = resolveImagePath(path);
    img = cv::imread(resolvedPath.string(), cv::IMREAD_UNCHANGED);
    if (img.empty()) {
        throw std::runtime_error("Cannot load image: " + resolvedPath.string());
    }

    if (size.first != 0 && size.second != 0) {  // Check if size is not empty
        int target_w = size.first;
        int target_h = size.second;
        int h = img.rows;
        int w = img.cols;

        if (keep_aspect) {
            double scale = std::min(static_cast<double>(target_w) / w, 
                                   static_cast<double>(target_h) / h);
            int new_w = static_cast<int>(w * scale);
            int new_h = static_cast<int>(h * scale);
            cv::resize(img, img, cv::Size(new_w, new_h), 0, 0, interpolation);
        } else {
            cv::resize(img, img, cv::Size(target_w, target_h), 0, 0, interpolation);
        }
    }

    return *this;
}

void Img::draw_on(Img& other_img, int x, int y) {
    if (img.empty() || other_img.img.empty()) {
        throw std::runtime_error("Both images must be loaded before drawing.");
    }

    cv::Mat source_img = img;
    cv::Mat target_img = other_img.img;

    int h = source_img.rows;
    int w = source_img.cols;
    int H = target_img.rows;
    int W = target_img.cols;

    if (y + h > H || x + w > W) {
        throw std::runtime_error("Image does not fit at the specified position.");
    }

    cv::Mat roi = target_img(cv::Rect(x, y, w, h));

if (source_img.channels() == 4) {
    std::vector<cv::Mat> srcChannels;
    cv::split(source_img, srcChannels);

    cv::Mat alpha;
    srcChannels[3].convertTo(alpha, CV_64FC1, 1.0 / 255.0);

    std::vector<cv::Mat> roiChannels;
    cv::split(roi, roiChannels);

    for (int c = 0; c < 3; ++c) {
        cv::Mat srcF, dstF, blendedF;
        srcChannels[c].convertTo(srcF, CV_64FC1);
        roiChannels[c].convertTo(dstF, CV_64FC1);

        blendedF = alpha.mul(srcF) + (1.0 - alpha).mul(dstF);
        blendedF.convertTo(roiChannels[c], roiChannels[c].type());
    }

    cv::merge(roiChannels, roi);
}    else {
        source_img.copyTo(roi);
    }
}

void Img::put_text(const std::string& txt, int x, int y, double font_size,
                   const cv::Scalar& color, int thickness) {
    if (img.empty()) {
        throw std::runtime_error("Image not loaded.");
    }
    
    cv::putText(img, txt, cv::Point(x, y),
                cv::FONT_HERSHEY_SIMPLEX, font_size,
                color, thickness, cv::LINE_AA);
}

void Img::show() {
    if (img.empty()) {
        throw std::runtime_error("Image not loaded.");
    }
    
    cv::imshow("Image", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
} 

Img& Img::create(int width, int height, const cv::Scalar& color) {
    img = cv::Mat(height, width, CV_8UC4, color);
    return *this;
}
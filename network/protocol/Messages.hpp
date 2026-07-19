
#include <optional>
#include <string>
#include <vector>

namespace protocol {

// --- Client -> Server -------------------------------------------------

struct LoginMessage {
    std::string username;
    std::string password;
};

struct CreateRoomMessage {
    std::string room_name;
};

struct JoinRoomMessage {
    std::string room_name;
};

struct QuickPlayMessage {
    // empty payload
};

struct ClickMessage {
    int x;
    int y;
};

struct LeaveMessage {
    // empty payload
};

// --- Server -> Client ---------------------------------------------------

struct LoginResultMessage {
    bool success;
    std::optional<std::string> reason;   // set when success == false
    std::optional<int> rating;           // set when success == true
};

struct RoomJoinedMessage {
    std::string room_id;
    std::string role;   // "white" | "black" | "spectator"
};

struct MatchmakingResultMessage {
    bool success;
    std::optional<std::string> room_id;  // set when success == true
    std::optional<std::string> reason;   // set when success == false
};

// Mirrors engine/GameSnapshot.hpp's PieceSnapshot field-for-field. Kept as
// its own type here rather than reusing PieceSnapshot directly, so
// network/protocol/ has no dependency on engine/ - connecting the two is
// deferred to the step that actually serializes a real GameSnapshot.
struct SnapshotPieceMessage {
    std::string pieceCode;
    int pixelX;
    int pixelY;
    std::string animState;
    int frameIndex;
};

struct SnapshotCell {
    int row;
    int col;
};

// Mirrors engine/GameSnapshot.hpp's GameSnapshot field-for-field.
struct SnapshotMessage {
    int rows;
    int cols;
    std::vector<SnapshotPieceMessage> pieces;
    std::optional<SnapshotCell> selectedCell;
    bool gameOver;
};

struct OpponentDisconnectedMessage {
    int countdown_seconds;
};

struct GameOverResultMessage {
    std::optional<std::string> winner;   // "white" | "black" | nullopt for a draw
    std::string reason;
};

struct ErrorMessage {
    std::string message;
};

}
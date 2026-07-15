cmake_minimum_required(VERSION 3.14)
project(kungfu_chess CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# הוספת תיקיית השורש לנתיבי החיפוש
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
cmake_minimum_required(VERSION 3.14)
project(kungfu_chess CXX)

# הגדרת תקן C++ (מומלץ להשתמש ב-17 ומעלה עבור פרויקטים מודרניים)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# הוספת תיקיית ה-include כדי שהקומפיילר ימצא את קובצי ה-.hpp
include_directories(include)

# איסוף כל קובצי המקור מתיקיית src
file(GLOB_RECURSE APP_SOURCES "src/*.cpp")

# הסרת main.cpp מהרשימה כדי שנוכל להשתמש בשאר הקבצים גם עבור הבדיקות
list(REMOVE_ITEM APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# --- בניית התוכנית הראשית ---
add_executable(kungfu_chess src/main.cpp ${APP_SOURCES})

# --- בניית מערך הבדיקות (Doctest) ---
enable_testing()

# איסוף קובצי הבדיקות
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

# יצירת קובץ הרצה נפרד לבדיקות
add_executable(test_runner ${TEST_SOURCES} ${APP_SOURCES})

# הוספת תיקיית tests כדי למצוא את doctest.h
target_include_directories(test_runner PRIVATE tests)

# רישום הבדיקה במערכת CTest
add_test(NAME run_doctest COMMAND test_runner)
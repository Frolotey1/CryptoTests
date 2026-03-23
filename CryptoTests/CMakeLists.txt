cmake_minimum_required(VERSION 3.5)

project(CryptoTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_NLOHMANN "${CMAKE_SOURCE_DIR}/json/include")

add_executable(CryptoTest main.cpp
    Authorization.cpp
    Ciphers.cpp
    TaskGenerator.cpp
    CryptoTestEasy.cpp
    Levels.cpp
    RunApplication.cpp
    TestEasyFixed.cpp
    TaskGenerator.h
    Ciphers.h
    Header.h
    CryptoTestEasy.h
    Levels.h
    RunApplication.h
    TestEasyFixed.h
    Authorization.h
)

target_include_directories(CryptoTest PRIVATE "${INCLUDE_NLOHMANN}")

include(GNUInstallDirs)
install(TARGETS CryptoTest
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

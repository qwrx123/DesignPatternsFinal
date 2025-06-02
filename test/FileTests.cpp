#include <gtest/gtest.h>
#include <filesystem>
#include "Export.h"

TEST(FileTests, FolderExists) {
    Export exportFile = Export();
    std::string location = exportFile.quarryFileLocation();
    
    std::filesystem::path path(location);
    EXPECT_TRUE(std::filesystem::exists(path));
}
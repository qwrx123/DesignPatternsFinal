#include <gtest/gtest.h>
#include <filesystem>
#include "Export.h"

TEST(FileTests, FolderExists) {
    Export exportFile = Export();
    std::string location = exportFile.quarryFileLocation();
    
    std::filesystem::path path(location);
    EXPECT_TRUE(std::filesystem::exists(path));
}

TEST(FileTests, emptyFile) {
    Export exportFile = Export();
    fileStruct fileStruct = {nullptr, 0};

    EXPECT_EQ(exportFile.exportFile(std::move(fileStruct)), false);
}
/**
 * @file
 *
 * @author feliwir
 *
 * @brief Set of tests to validate the CRC32 implementation
 *
 * @copyright Thyme is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#include <string>
#include <gamespy.h>
#include <gtest/gtest.h>

TEST(Gamespy, KeyValueExtract)
{
    const char* original_string = "\\lc\\1\\challenge\\DFDMXJLXJL\\id\\1\\final\\";
    const char* key = "\\challenge\\";
    const char* notkey = "\\notakey\\";
    char buf[128];

    auto ok = GamespyProtocol::ValueForKey(original_string, key, buf, 0x80);

    EXPECT_EQ(ok, 1);
    EXPECT_STREQ(buf, "DFDMXJLXJL");

    // auto not_ok = GamespyProtocol::ValueForKey(original_string, notkey, buf, 0x80);
    // EXPECT_EQ(ok, 0);
}

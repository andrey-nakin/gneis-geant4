#include <gtest/gtest.h>
#include "gneis/util/FileNameBuilder.hh"

namespace gneis {

namespace util {

TEST(FileNameBuilder, Make_pch_pch)
{
	G4String const res = FileNameBuilder::Make("base", ".txt");
	EXPECT_EQ("base.txt", res);
}

TEST(FileNameBuilder, Make_s_pch)
{
	G4String const res = FileNameBuilder::Make(G4String("base"), ".txt");
	EXPECT_EQ("base.txt", res);
}

TEST(FileNameBuilder, MakeWithCommonSuffix_pch_pch)
{
	FileNameBuilder::SetCommonSuffix("abc");
	G4String const res = FileNameBuilder::Make("base", ".txt");
	EXPECT_EQ("base.abc.txt", res);
}

TEST(FileNameBuilder, MakeWithCommonSuffix_s_pch)
{
	FileNameBuilder::SetCommonSuffix("abc");
	G4String const res = FileNameBuilder::Make(G4String("base"), ".txt");
	EXPECT_EQ("base.abc.txt", res);
}

}

}

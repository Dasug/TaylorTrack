//
// Created by Jannis Hoppe on 28.01.16.
//


#include "../utils/fft_lib.h"
#include "gtest/gtest.h"

TEST(FftLibTest,FftTest) {
    taylortrack::utils::FftLib::CArray vec(8);
    vec[0] = 1;
    vec[1] = 1;
    vec[2] = 1;
    vec[3] = 1;
    vec[4] = 0;
    vec[5] = 7;
    vec[6] = 2;
    vec[7] = 2;
    taylortrack::utils::FftLib FftLib = taylortrack::utils::FftLib();
    FftLib.fft(vec);
    // testing real parts
    ASSERT_TRUE(std::abs(vec[0].real()-15) < 0.0001);
    ASSERT_TRUE(std::abs(vec[1].real()+2.53553) < 0.0001);
    ASSERT_TRUE(std::abs(vec[2].real()+2) < 0.0001);
    ASSERT_TRUE(std::abs(vec[3].real()-4.53553) < 0.0001);
    ASSERT_TRUE(std::abs(vec[4].real()+7) < 0.0001);
    ASSERT_TRUE(std::abs(vec[5].real()-4.53553) < 0.0001);
    ASSERT_TRUE(std::abs(vec[6].real()+2) < 0.0001);
    ASSERT_TRUE(std::abs(vec[7].real()+2.53553) < 0.0001);
    // testing complex parts
    ASSERT_TRUE(std::abs(vec[0].imag()) < 0.0001);
    ASSERT_TRUE(std::abs(vec[1].imag()-5.9497) < 0.0001);
    ASSERT_TRUE(std::abs(vec[2].imag()+5) < 0.0001);
    ASSERT_TRUE(std::abs(vec[3].imag()-3.9497) < 0.0001);
    ASSERT_TRUE(std::abs(vec[4].imag()) < 0.0001);
    ASSERT_TRUE(std::abs(vec[5].imag()+3.9497) < 0.0001);
    ASSERT_TRUE(std::abs(vec[6].imag()-5) < 0.0001);
    ASSERT_TRUE(std::abs(vec[7].imag()+5.9497) < 0.0001);

};

TEST(FftLibTest,IfftTest) {
    taylortrack::utils::FftLib::CArray vec(8);
    vec[0] = 1;
    vec[1] = 1;
    vec[2] = 1;
    vec[3] = 1;
    vec[4] = 0;
    vec[5] = 7;
    vec[6] = 2;
    vec[7] = 2;
    taylortrack::utils::FftLib FftLib = taylortrack::utils::FftLib();

    FftLib.fft(vec);
    FftLib.ifft(vec);
    ASSERT_TRUE(vec[0].real()-1 < 0.0001);
    ASSERT_TRUE(vec[1].real()-1 < 0.0001);
    ASSERT_TRUE(vec[2].real()-1 < 0.0001);
    ASSERT_TRUE(vec[3].real()-1 < 0.0001);
    ASSERT_TRUE(vec[4].real() < 0.0001);
    ASSERT_TRUE(vec[5].real()-7 < 0.0001);
    ASSERT_TRUE(vec[6].real()-2 < 0.0001);
    ASSERT_TRUE(vec[7].real()-2 < 0.0001);
    ASSERT_TRUE(std::abs(vec[0].imag()) < 0.00001);
    ASSERT_TRUE(std::abs(vec[1].imag()) < 0.00001);
    ASSERT_TRUE(std::abs(vec[2].imag()) < 0.00001);
    ASSERT_TRUE(std::abs(vec[3].imag()) < 0.00001);
    ASSERT_TRUE(std::abs(vec[4].imag()) < 0.00001);
    ASSERT_TRUE(std::abs(vec[5].imag()) < 0.00001);
    ASSERT_TRUE(std::abs(vec[6].imag()) < 0.00001);
    ASSERT_TRUE(std::abs(vec[7].imag()) < 0.00001);

};

TEST(FftLibTest,Circshifttest) {
    taylortrack::utils::FftLib::RArray vec(6);
    taylortrack::utils::FftLib::RArray outvec(6);
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;
    vec[3] = 4;
    vec[4] = 5;
    vec[5] = 6;
    outvec[0] = 1;
    outvec[1] = 2;
    outvec[2] = 3;
    outvec[3] = 4;
    outvec[4] = 5;
    outvec[5] = 6;
    taylortrack::utils::FftLib FftLib = taylortrack::utils::FftLib();
    FftLib.circshift(outvec,vec,1,6,0,2);

    ASSERT_EQ(outvec[0],5);
    ASSERT_EQ(outvec[1],6);
    ASSERT_EQ(outvec[2],1);
    ASSERT_EQ(outvec[3],2);
    ASSERT_EQ(outvec[4],3);
    ASSERT_EQ(outvec[5],4);
}

TEST(FftLibTest,Fftshifttest) {
    taylortrack::utils::FftLib::RArray vec(6);
    taylortrack::utils::FftLib::RArray outvec(6);
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;
    vec[3] = 4;
    vec[4] = 5;
    vec[5] = 6;
    outvec[0] = 1;
    outvec[1] = 2;
    outvec[2] = 3;
    outvec[3] = 4;
    outvec[4] = 5;
    outvec[5] = 6;
    taylortrack::utils::FftLib FftLib = taylortrack::utils::FftLib();
    FftLib.fftshift(outvec,vec);

    ASSERT_EQ(outvec[0],4);
    ASSERT_EQ(outvec[1],5);
    ASSERT_EQ(outvec[2],6);
    ASSERT_EQ(outvec[3],1);
    ASSERT_EQ(outvec[4],2);
    ASSERT_EQ(outvec[5],3);
}

// suspected memory errors in this test
TEST(FftLibTest,Zeropadding_Test) {
    taylortrack::utils::FftLib::CArray vec(8);
    taylortrack::utils::FftLib::CArray newvec(16);
    vec[0] = 0.1;
    vec[1] = 0.2;
    vec[2] = 0.3;
    vec[3] = 0.4;
    vec[4] = 0.5;
    vec[5] = 0.6;
    vec[6] = 0.7;
    vec[7] = 0.8;
    taylortrack::utils::FftLib FftLib = taylortrack::utils::FftLib();
    newvec = FftLib.zeropadding(vec,8);

    ASSERT_EQ(newvec.size(),16);
    ASSERT_EQ(newvec[0].real(),0.1);
    ASSERT_EQ(newvec[1].real(),0.2);
    ASSERT_EQ(newvec[2].real(),0.3);
    ASSERT_EQ(newvec[3].real(),0.4);
    ASSERT_EQ(newvec[4].real(),0.5);
    ASSERT_EQ(newvec[5].real(),0.6);
    ASSERT_EQ(newvec[6].real(),0.7);
    ASSERT_EQ(newvec[7].real(),0.8);
    ASSERT_EQ(newvec[8].real(),0);
    ASSERT_EQ(newvec[9].real(),0);
    ASSERT_EQ(newvec[10].real(),0);
}
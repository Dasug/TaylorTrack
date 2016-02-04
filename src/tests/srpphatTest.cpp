//
// Created by Jannis Hoppe on 31.01.16.
//
#include "../localization/srpphat.h"
#include "gtest/gtest.h"
#include "../utils/fft_lib.h"

#include <math.h>

TEST(SrpPhatTest,imtdfTest) {
    taylortrack::utils::FftLib::RArray point(2);
    taylortrack::utils::FftLib::RArray mic1(2);
    taylortrack::utils::FftLib::RArray mic2(2);
    taylortrack::utils::FftLib::RArray mics(4);

    taylortrack::localization::SrpPhat srp = taylortrack::localization::SrpPhat(44100, 2000,mics, mics,0,0,0);

    point[0] = 0;
    point[1] = 339.42;
    mic1[0] = 1;
    mic1[0] = 0;
    mic2[0] = -1;
    mic2[0] = 0;

    double difference = srp.imtdf(point, mic1, mic2);
    ASSERT_EQ(difference,0.0);
}

TEST(SrpPhatTest,prodTest) {
    taylortrack::utils::FftLib::RArray point(3);
    taylortrack::utils::FftLib::RArray point2(3);
    point[0] = 0.5;
    point[1] = 1;
    point[2] = 2;
    point2[0] = 3.0;
    point2[1] = 4.0;
    point2[2] = 5.0;

    point = point/point2;
    taylortrack::utils::FftLib::CArray point3 = taylortrack::utils::FftLib::converttocomp(point);
    for (int i=0;i<3;i++){
        std::cout << point3[i]<< "\n";
    }


    ASSERT_EQ(1,1);
}

TEST(SrpPhatTest,gccTest) {
    taylortrack::utils::FftLib::RArray mics(4);
    double p1[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7,0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
    double p2[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8,0.9,1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
    taylortrack::utils::FftLib::RArray point(p1,17);
    taylortrack::utils::FftLib::RArray point2(p2,16);

    taylortrack::localization::SrpPhat srp = taylortrack::localization::SrpPhat(44100, 2000, mics,mics,0,0,0);


    taylortrack::utils::FftLib::RArray gcca = srp.gcc(point,point2,0.7);


    ASSERT_TRUE(abs(gcca.max()-1.51588) < 0.0001);
}

TEST(SrpPhatTest,pointToAngleTest) {
    int x = 1;
    int y = 1;
    int x2 = 0;
    int y2 = -1;
    int x3 = -1;
    int y3 = 0;
    double x4 = 1.4153;
    double y4 = 5.41;
    taylortrack::utils::FftLib::RArray mics(4);
    taylortrack::localization::SrpPhat srp = taylortrack::localization::SrpPhat(44100, 2000, mics,mics,0,0,0);
    int deg = srp.pointToAngle(x,y);
    int deg2 = srp.pointToAngle(x2,y2);
    int deg3 = srp.pointToAngle(x3,y3);
    int deg4 = srp.pointToAngle(x4,y4);
    int deg5 = srp.pointToAngle(x4,-y4);
    ASSERT_EQ(45,deg);
    ASSERT_EQ(270,deg2);
    ASSERT_EQ(180,deg3);
    ASSERT_EQ(75,deg4);
    ASSERT_EQ(285,deg5);
}

TEST(SrpPhatTest,getDelayTensorTest) {
    double mx[] = {0.05, 0.00, -0.05, 0.00};
    double my[] = {0.00, 0.05, 0.00, -0.05};
    taylortrack::utils::FftLib::RArray micsX(mx,4);
    taylortrack::utils::FftLib::RArray micsY(my,4);
    taylortrack::localization::SrpPhat srp = taylortrack::localization::SrpPhat(44100, 2000, micsX,micsX,4.0,4.0,0.1);

    std::vector<std::vector<std::vector<double>>> difference;
    difference = srp.getDelayTensor();
    ASSERT_EQ(0,0);
}

TEST(SrpPhatTest,getMicPairsTest) {
    taylortrack::utils::FftLib::RArray mics(4);

    taylortrack::localization::SrpPhat srp = taylortrack::localization::SrpPhat(44100, 2000, mics,mics,4.0,4.0,0.1);

    std::vector< std::tuple<int,int>> micP = srp.getMicPairs();

    ASSERT_EQ(0,std::get<0>(micP[0]));
    ASSERT_EQ(1,std::get<1>(micP[0]));
    ASSERT_EQ(0,std::get<0>(micP[1]));
    ASSERT_EQ(2,std::get<1>(micP[1]));
    ASSERT_EQ(0,std::get<0>(micP[2]));
    ASSERT_EQ(3,std::get<1>(micP[2]));
    ASSERT_EQ(1,std::get<0>(micP[3]));
    ASSERT_EQ(2,std::get<1>(micP[3]));
    ASSERT_EQ(1,std::get<0>(micP[4]));
    ASSERT_EQ(3,std::get<1>(micP[4]));
    ASSERT_EQ(2,std::get<0>(micP[5]));
    ASSERT_EQ(3,std::get<1>(micP[5]));

}
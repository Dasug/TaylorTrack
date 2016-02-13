//
// Created by Jannis Hoppe on 31.01.16.
//
#include "../localization/srpphat.h"
#include "gtest/gtest.h"
#include "../utils/fft_lib.h"

#include <math.h>
#include <fstream>

TEST(SrpPhatTest,imtdfTest) {
    taylortrack::utils::RArray point(2);
    taylortrack::utils::RArray point2(2);
    taylortrack::utils::RArray mic1(2);
    taylortrack::utils::RArray mic2(2);
    taylortrack::utils::RArray mics(4);

    taylortrack::localization::SrpPhat srp = taylortrack::localization::SrpPhat(44100,mics, mics,0,0,0,256,0.7);

    point[0] = 0;
    point[1] = 339.42;
    mic1[0] = 1;
    mic1[1] = 0;
    mic2[0] = -1;
    mic2[1] = 0;

    double difference = srp.imtdf(point, mic1, mic2);
    ASSERT_EQ(0.0,difference);

    point2[0] = -2;
    point2[1] = 2;
    mic1[0] = -0.05;
    mic1[1] = 0;
    mic2[0] = 0.05;
    mic2[1] = 0;
    double difference2 = srp.imtdf(point2, mic1, mic2);
    ASSERT_TRUE(abs(difference2-0.0002077) < 0.000001);
}

TEST(SrpPhatTest,axisValueTest) {
    std::vector<taylortrack::utils::FftLib::RArray> vec;
    taylortrack::utils::RArray point(3);
    double mx[] = {0.0, -0.055, 0, 0.055};
    double my[] = {0.055, 0.0, -0.055, 0.0};
    taylortrack::utils::RArray micsX(mx,4);
    taylortrack::utils::RArray micsY(my,4);
    taylortrack::localization::SrpPhat srp = taylortrack::localization::SrpPhat(44100, micsX,micsY,4.0,4.0,0.1,256,0.7);

    std::vector<double> xax = srp.getAxisvalues(true);
    std::vector<double> yax = srp.getAxisvalues(false);

    for (int i=0;i<xax.size();i++){
        std::cout << xax[i]<< "\n";
        std::cout << yax[i]<< "\n";

    }
    std::cout << xax.size()<< "\n";

    ASSERT_EQ(1,1);
}

TEST(SrpPhatTest,gccTest) {




    taylortrack::utils::RArray mics(4);
    taylortrack::localization::SrpPhat srp = taylortrack::localization::SrpPhat(44100, mics,mics,0,0,0,256,0.7);

    taylortrack::utils::RArray sig1 = srp.getMicSignal("../Testdata/0-180.txt");
    taylortrack::utils::RArray sig2 = srp.getMicSignal("../Testdata/90-180.txt");

    taylortrack::utils::RArray temp1 = sig1[std::slice(0,257,1)];
    taylortrack::utils::RArray temp2 = sig2[std::slice(0,256,1)];

    taylortrack::utils::RArray gcca = srp.gcc(temp1,temp2);


    ASSERT_TRUE(abs(gcca.max()-0.0138) < 0.0001);
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
    double x5 = 0;
    double y5 = 0;
    taylortrack::utils::RArray mics(4);
    taylortrack::localization::SrpPhat srp = taylortrack::localization::SrpPhat(44100, mics,mics,0,0,0,256,0.7);
    int deg = srp.pointToAngle(x,y);
    int deg2 = srp.pointToAngle(x2,y2);
    int deg3 = srp.pointToAngle(x3,y3);
    int deg4 = srp.pointToAngle(x4,y4);
    int deg5 = srp.pointToAngle(x4,-y4);
    int deg6 = srp.pointToAngle(x5,y5);
    ASSERT_EQ(45,deg);
    ASSERT_EQ(270,deg2);
    ASSERT_EQ(180,deg3);
    ASSERT_EQ(75,deg4);
    ASSERT_EQ(285,deg5);
    ASSERT_EQ(0,deg6);

}

TEST(SrpPhatTest,getDelayTensorTest) {
    double mx[] = {0.0, -0.055, 0, 0.055};
    double my[] = {0.055, 0.0, -0.055, 0.0};
    taylortrack::utils::RArray micsX(mx,4);
    taylortrack::utils::RArray micsY(my,4);

    taylortrack::localization::SrpPhat srp = taylortrack::localization::SrpPhat(44100, micsX,micsY,4.0,4.0,0.1,256,0.7);

    std::vector<std::vector<std::vector<double>>> difference;

    difference = srp.getDelayTensor();
    std::cout << difference.size()<< "\n";
    ASSERT_EQ(0,0);
}

TEST(SrpPhatTest,getMicPairsTest) {
    taylortrack::utils::RArray mics(4);

    taylortrack::localization::SrpPhat srp = taylortrack::localization::SrpPhat(44100, mics,mics,4.0,4.0,0.1,256,0.7);

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

TEST(SrpPhatTest,gccGridTest) {

    double mx[] = {0.0, -0.055, 0, 0.055};
    double my[] = {0.055, 0.0, -0.055, 0.0};
    double beta = 0.7;
    taylortrack::utils::RArray micsX(mx,4);
    taylortrack::utils::RArray micsY(my,4);
    taylortrack::localization::SrpPhat srp = taylortrack::localization::SrpPhat(44100, micsX,micsY,4.0,4.0,0.1,256,beta);

    taylortrack::utils::RArray sig1 = srp.getMicSignal("../Testdata/0-180.txt");
    taylortrack::utils::RArray sig2 = srp.getMicSignal("../Testdata/90-180.txt");
    taylortrack::utils::RArray sig3 = srp.getMicSignal("../Testdata/180-180.txt");
    taylortrack::utils::RArray sig4 = srp.getMicSignal("../Testdata/270-180.txt");

    std::vector<taylortrack::utils::RArray> signals;
    signals.push_back(sig1);
    signals.push_back(sig2);
    signals.push_back(sig3);
    signals.push_back(sig4);
    std::vector<std::vector<double>> gcca = srp.getGccGrid(signals);
    for (int i=0;i<41;i++){
        for(int j=0;j<41;j++){
            std::cout << gcca[i][j]<< " ";
        }
        std::cout << "\n"<< std::endl;
    }


    ASSERT_TRUE(true);
}

TEST(SrpPhatTest,getPositionTest) {

    double mx[] = {0.0, -0.055, 0, 0.055};
    double my[] = {0.055, 0.0, -0.055, 0.0};
    taylortrack::utils::FftLib::RArray micsX(mx,4);
    taylortrack::utils::FftLib::RArray micsY(my,4);
    const int steps = 256;
    taylortrack::localization::SrpPhat srp = taylortrack::localization::SrpPhat(44100, micsX,micsY,4.0,4.0,0.1,steps,0.7);

    taylortrack::utils::FftLib::RArray sig1 = srp.getMicSignal("../Testdata/0-180.txt");
    taylortrack::utils::FftLib::RArray sig2 = srp.getMicSignal("../Testdata/90-180.txt");
    taylortrack::utils::FftLib::RArray sig3 = srp.getMicSignal("../Testdata/180-180.txt");
    taylortrack::utils::FftLib::RArray sig4 = srp.getMicSignal("../Testdata/270-180.txt");




    std::vector<taylortrack::utils::FftLib::RArray> signals;
    signals.push_back(sig1);
    signals.push_back(sig2);
    signals.push_back(sig3);
    signals.push_back(sig4);
    int signalLength = signals[0].size();
    int sigsteps = signalLength / 2570 +1;
    for(int step=1;step<sigsteps;step++){
        std::vector<taylortrack::utils::FftLib::RArray> signals2;

        taylortrack::utils::FftLib::RArray signalSlice1 = sig1[std::slice((2570-1)*(step-1), 2570, 1)];
        taylortrack::utils::FftLib::RArray signalSlice2 = sig2[std::slice((2570-1)*(step-1), 2570, 1)];
        taylortrack::utils::FftLib::RArray signalSlice3 = sig3[std::slice((2570-1)*(step-1), 2570, 1)];
        taylortrack::utils::FftLib::RArray signalSlice4 = sig4[std::slice((2570-1)*(step-1), 2570, 1)];
        signals2.push_back(signalSlice1);
        signals2.push_back(signalSlice2);
        signals2.push_back(signalSlice3);
        signals2.push_back(signalSlice4);
        std::vector<std::vector<double>> gcca = srp.getGccGrid(signals2);
        int pos = srp.getPosition(gcca);
        std::cout << pos<< std::endl;
    }
    //int gcca = srp.getPosition(signals);



    ASSERT_TRUE(true);
}
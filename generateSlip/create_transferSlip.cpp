#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace cv;
using namespace std;

string getDisplayTime()         {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_mday << "/"
       << setw(2) << 1 + ltm->tm_mon << "/"
       << 1900 + ltm->tm_year << " "
       << setw(2) << ltm->tm_hour << ":"
       << setw(2) << ltm->tm_min << ":"
       << setw(2) << ltm->tm_sec;
    return ss.str();
}

string getSafeFileName() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
       << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
       << setw(2) << ltm->tm_mday << "_"
       << setw(2) << ltm->tm_hour 
       << setw(2) << ltm->tm_min
       << setw(2) << ltm->tm_sec;
    return ss.str();
}

void generateSlipTransferPNG(string bankID1, string n1, string bankID2, string n2, double amount) {
    string savePath = "C:/Users/Admin/Pictures/slips/";
    string templatePath = "E:/Projects/p1/generateSlip/templateTransfer.png";

    Mat slip = imread(templatePath);
    if (slip.empty()) {
        cout << "[Error] Find template.png NOT FOUND in current folder!" << endl;
        return; 
    }

    int font = FONT_HERSHEY_DUPLEX;
    Scalar black(40, 40, 40);
    Scalar green(0, 150, 0);
    int imgWidth = slip.cols; 

    string displayTime = getDisplayTime();
    string safeTime = getSafeFileName();

    Size timeSize = getTextSize(displayTime, font, 1.2, 1, 0);
    putText(slip, displayTime, Point((imgWidth - timeSize.width) / 2, 640), font, 1.2, black, 1, LINE_AA);

    stringstream ssAmt;
    ssAmt << fixed << setprecision(2) << amount;
    string amtStr = ssAmt.str();
    Size amtSize = getTextSize(amtStr, font, 2.8, 3, 0);
    putText(slip, amtStr, Point((imgWidth - amtSize.width) / 2, 965), font, 2.8, green, 3, LINE_AA);

    putText(slip, n1, Point(516, 1262), font, 2, black, 2, LINE_AA);
    putText(slip, bankID1, Point(513, 1370), font, 1.7, black, 2, LINE_AA);

    putText(slip, n2, Point(516, 1550), font, 2, black, 2, LINE_AA);
    putText(slip, bankID2, Point(513, 1666), font, 1.7, black, 2, LINE_AA);

    string filename = "Slip_" + safeTime + ".png";
    vector<int> compression_params = {IMWRITE_PNG_COMPRESSION, 0};
    
    bool success = imwrite(savePath + filename, slip, compression_params);

    if (success) cout << "[OpenCV] Success! Saved to: " << savePath + filename << endl;
    else cout << "[Error] Could not save the generated image!" << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 6) { 
        cout << "[System] Usage: id1 n1 id2 n2 amount\n";
        return 0;
    }

    string id1 = argv[1];
    string name1 = argv[2]; 
    string id2 = argv[3];
    string name2 = argv[4];
    double amount = stod(argv[5]);

    generateSlipTransferPNG(id1, name1, id2, name2, amount); 
    return 0;
}
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace cv;
using namespace std;

string getCurrentTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;

    ss << setfill('0') << setw(2) << ltm->tm_mday << "/"
       << setw(2) << 1 + ltm->tm_mon << "/"
       << 1900 + ltm->tm_year << " "
       << setw(2) << ltm->tm_hour << ":"
       << setw(2) << ltm->tm_min;
    return ss.str();
}

string getSafeFileName()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;

    ss << 1900 + ltm->tm_year << "-"
       << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
       << setw(2) << ltm->tm_mday << "_"
       << setw(2) << ltm->tm_hour << setw(2) << ltm->tm_min;
    return ss.str();
}

void generateSlipPNG(string templateType, string bankID, string type, double amount, double balance) {
    string savePath = "C:/Users/Admin/Pictures/slips/";
    string templatePath = "";
    if (templateType == "white") templatePath = "E:\\Projects\\p1\\generateSlip\\white_template.png";

    Mat slip = imread(templatePath);
    if (slip.empty()) {
        cout << "[Error] Could not open or find the image: " << templatePath << endl;
        cout << "Please make sure the template file is in the correct folder." << endl;
        return; 
    }

    int font = FONT_HERSHEY_DUPLEX;
    Scalar black(0, 0, 0); 
    Scalar green(0, 150, 0);

    string displayTime = getCurrentTime();
    string safeTime = getSafeFileName();

    putText(slip, "FAM SOD BANK", Point(85, 55), FONT_HERSHEY_TRIPLEX, 1.0, black, 2, LINE_AA);
    line(slip, Point(20, 80), Point(380, 80), black, 2, LINE_AA);

    putText(slip, "Date: " + displayTime, Point(30, 120), font, 0.6, black, 1, LINE_AA);
    putText(slip, "Acc No: " + bankID, Point(30, 150), font, 0.6, black, 1, LINE_AA);
    putText(slip, "Type: " + type, Point(30, 180), font, 0.6, black, 1, LINE_AA);

    stringstream ssAmt;
    ssAmt << fixed << setprecision(2) << amount;
    
    rectangle(slip, Point(20, 210), Point(380, 280), Scalar(245, 245, 245), FILLED);
    putText(slip, "AMOUNT", Point(40, 235), font, 0.5, Scalar(100, 100, 100), 1, LINE_AA);
    putText(slip, ssAmt.str() + " THB", Point(120, 260), font, 1.1, green, 2, LINE_AA);

    stringstream ssBal;
    ssBal << fixed << setprecision(2) << balance;
    putText(slip, "Balance: " + ssBal.str() + " THB", Point(30, 320), font, 0.6, black, 1, LINE_AA);

    line(slip, Point(20, 420), Point(380, 420), Scalar(200, 200, 200), 1, LINE_AA);
    putText(slip, "Thank you for using our service", Point(65, 450), font, 0.5, Scalar(120, 120, 120), 1, LINE_AA);

    string filename = "Slip_" + type + "_" + safeTime + ".png";
    vector<int> compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(0);

    bool success = imwrite(savePath + filename, slip, compression_params);

    if (success) cout << "[OpenCV] Success! Slip generated on template: " << filename << endl;
    else cout << "[Error] Could not save the generated image!" << endl;
}

int main() {
    generateSlipPNG("white", "123-456-7890", "DEPOSIT", 5000.50, 12000.00);
    return 0;
}
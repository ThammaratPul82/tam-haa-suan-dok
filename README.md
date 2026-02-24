# tam-haa-suan-dok

#generateSlip
    ONLY!!! -> OpenCV (MSYS2)
    
    how to build: 
        g++ create_img.cpp -o create_img -I "C:/msys64/ucrt64/include/opencv4" -lopencv_core -lopencv_imgproc -lopencv_imgcodecs

    how to use function:
        all parameter is string.
        type "1": deposit, "2": withdrawal
        
        ex. createIMG(id, type, amount, balance);
        createIMG("680610xxx", "2", "1000", "999999");
#include <torch/torch.h> // One-stop header.
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <torch/script.h>
#include <memory>
#include <torch/csrc/jit/passes/tensorexpr_fuser.h>


int main() {

    // Load your traced model
    torch::jit::script::Module module;
    try
    {
        module = torch::jit::load("traced_model.pt");
    }
    catch (const c10::Error& e)
    {
        std::cerr << "error loading the model\n";
        return -1;
    }
    // This method is added due to error in forwarding
    torch::jit::setTensorExprFuserEnabled(false);
    
    // Create Video Capture Object to read frames
    cv::VideoCapture cap;
    cap.open("yourvideo.mp4", cv::CAP_ANY);
    cv::Mat frame, img_float;
    
    // To convert OpenCv Image to pytorch tensor the type may vary according to your model
    torch::TensorOptions options(torch::kFloat32);
    torch::Tensor input_tensor;
    std::vector<torch::jit::IValue> inputs; // Traced model accept inputs as Ivalue
    while(true)
    {
        cap.read(frame);
        if (frame.empty())
        {
            std::cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        // Convert OpenCv Image to Pytorch tensor
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        cv::resize(frame, frame, cv::Size(256, 256));
        frame.convertTo(img_float, CV_32FC3, 1.0f/255.0f);
        input_tensor = torch::from_blob(img_float.data, {1, img_float.rows, img_float.cols, 3}, options);
        
        // Torch accepts as CHW so permute the input from HWC to CHW
        input_tensor = input_tensor.permute({0,3,1,2});
        inputs.push_back(input_tensor);
        auto output_tensor = module.forward(inputs).toTensor();
        
        // Convert tensor to OpenCv image
        output_tensor = output_tensor.squeeze().detach().clamp(0, 1).permute({1, 2, 0});
        inputs.clear();
        cv::Mat output_tmp(cv::Size(256, 256) , CV_32FC3, output_tensor.data_ptr<float>());
        cv::cvtColor(output_tmp, output_tmp, cv::COLOR_RGB2BGR);
        cv::Mat network_output(output_tmp.size(), CV_8UC3);
        float scale_factor_up = 255.0;
        output_tmp.convertTo(network_output, CV_8UC3, scale_factor_up);

        cv::imshow("Deblurred Image", network_output);
        if (cv::waitKey(5) >= 0)
            break;

    }
    cv::destroyAllWindows();
    return 0;
}

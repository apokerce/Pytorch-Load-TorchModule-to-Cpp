# Pytorch torch.jit.trace
Pytorch allow users to trace their nn.module or python functions and create executable or ScriptFunction. This scripts then can be called using pytorch built in methods like jit.load(). In this repo, a python nn model which also has user defined functions is traced and called in C++ using qmake.



## Installations
### Python Side
  - It depends on the models requirements check the requirements.txt file if provided by the authors
### C++ Side
  - [Qt](https://wiki.qt.io/Install_Qt_5_on_Ubuntu) (5.15.2 Version is used in this repo)
  - [Libtorch](https://pytorch.org/)
  - [C++ and OpenCv](http://techawarey.com/programming/install-opencv-c-c-in-ubuntu-18-04-lts-step-by-step-guide/)

For installation guides of tools in C++ side you can click on the required tool.




## Code to Trace the Model in Python
```shell
$ traced_model = torch.jit.trace(model_object, example_input)
$ traced_model.save('traced_model.pt')
```

#### For More Information on Tracing Model
- [Tracing a Python Model](https://pytorch.org/tutorials/advanced/cpp_export.html)


## Usage
```shell
$ Do not forget to change the paths defined in pro file
$ Place your traced model in debug folder of your project
$ Change line 17 according to your input model
$ Change line 29 to your video input
$ Run the main.cpp code to observe the output
```


## CEC2021-Bound-Constrained-Opt_mpmL-SHADE & mL-SHADE & L-SHADE

### Authors:
 The source code of mpmL-SHADE is implemented by Yann-Chern Jou, Shuo-Ying Wang, Jia-Fong Yeh, and Tsung-Che Chiang.
 The source code of mL-SHADE is implemented by Jia-Fong Yeh, Ting-Yu Chen, and Tsung-Che Chiang.
 
 If you have any question about the algorithm or program, please contact us.

### About this repository
 We test three algorithms L-SHADE, mL-SHADE, and mpmL-SHADE in [CEC2021 Single Objective Bound Constrained Optimization Benchmarks](https://github.com/P-N-Suganthan/2021-SO-BCO "link"). In our experiment setting files, you can easily change the parameters to control Basic, Bias, Shift, and Rotation for each benchmark function. You can also test the benchmark function in two different dimensions(D = 10, 20).

### CEC2020 mpmL-SHADE:
 We participated the competitions of Real-World Single Objective Constrained Optimization in IEEE CEC2020 Special Session. The paper of our algorithm is published in [CEC2020](https://ieeexplore.ieee.org/abstract/document/9185735 "link") and the oral presentation video is presented in [NTNU MHLab YouTube channel](https://youtu.be/JMj0mHpIARw "link"). We extend a previous algorithm mL-SHADE by running the evolutionary process through multiple populations and adding dynamic control of mutation intensity and hyper-parameters. The whole population is partitioned into sub-populations by a random clustering method. Mutation intensity and hyper-parameters are adjusted based on the consumption of fitness function evaluations. Performance of the proposed algorithm is verified by ten benchmark functions in [CEC2020 Competition on Single Objective Bound Constrained Optimization](https://github.com/P-N-Suganthan/2020-Bound-Constrained-Opt-Benchmark "link").
 
### CEC2019 mL-SHADE:
 We participated the competitions of 100-Digit Challenge on Real-Parameter Single Objective Optimization in IEEE CEC2019 Special Session. The paper of our algorithm is published in [CEC2019](https://ieeexplore.ieee.org/document/8789991 "link") and the oral presentation slides are showed in [NTNU MHLab](https://web.ntnu.edu.tw/~tcchiang/publications/CEC2019/CEC2019a-mL-SHADE-slides.pdf "link"). We propose a modified LSHADE(mL-SHADE), in which three modifications are made: (1)
removal of the terminal value, (2) addition of polynomial mutation, and (3) proposal of a memory perturbation mechanism. Performance of the proposed algorithm is verified by ten benchmark functions in [CEC2019 Competition of 100-Digit Challenge on Single Objective Bound Constrained Optimization](https://github.com/P-N-Suganthan/CEC2019 "link").


### How to implement our program:
 We developed our program by C++ (std C++17). The development environment is Visual Studio 2019 under Win10(SDK: 10.0.18363)  
 
 The detail of executation is shown down below:  
   
 * __Step 1.__ Set the parameters in "experiment_list.ini"  
          **num_problem**: the number of benchmark function you are going to test  
          **probem_ID**: all the index of benchmark function you are going to test  
          **problem_setting**: Basic, Bias, Shift, and Rotation  
          **Dimension**: the dimensions of benchmark function(D = 10, 20)  
          **Algorithm**: the testing algorithms, such as L-SHADE, mL-SHADE, and mpmL-SHADE  
         
 * __Step 2.__ Set the parameters of each algorithm in "experiments" folder.
         
 * __Step 3.__ In the 'exp_problems' folder, we have all the parameters setting for each benchmark problem. Please make sure you have "input_data."
 
 * __Step 4.__ Then, You can execute the 'CEC2020-Bound-Constrained-Opt_mpmL-SHADE.exe' to run the experiments.  
   
   Note: If you also use our log system, please make sure the storage capacity of disk is more than 100GB.  
 
### About the results:
  Please check the "Results" folder.  
  All of computing results were proccessed by our helping program in the "Source Code\Tools" folders.

### References:
[1] J. Yeh, T. Chen and T. Chiang, "Modified L-SHADE for single objective real-parameter optimization," In: Proceedings of IEEE Congress on Evolutionary Computation (CEC2019), Wellington, New Zealand, 2019, pp. 381-386. [mL-SHADE]

[2] Y. Jou, S. Wang and T. Chiang, "Multi-population modified L-SHADE for single objective bound constrained optimization," In: Proceedings of IEEE Congress on Evolutionary Computation (CEC2020), Glasgow, United Kingdom, 2020, pp. 1-8, doi: 10.1109/CEC48606.2020.9185735. [mpmL-SHADE]

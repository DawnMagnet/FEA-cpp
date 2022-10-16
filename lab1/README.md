# 作业1

1. 结合书本初步构建TrussSolveFramework，使用方法如下所示
   ```cpp
   TrussSolveFramework *tsf = new TrussSolveFramework();
   tsf->initEA(2e11, 4e-4)
           ->add(TrussPoint(0, 0))                        // point0
           ->add(TrussPoint(0, 3))                        // point1
           ->add(TrussPoint(3.0 / sqrt(2), 3.0 / sqrt(2)))// point2
           ->add(TrussPoint(3, 0))                        // point3
           ->add(TrussEdge(0, 1))                         // edge1
           ->add(TrussEdge(0, 2))                         // edge2
           ->add(TrussEdge(0, 3))                         // edge3
           ->assemble();
   cout << "K-matrix:\n";
   tsf->showK();

   auto solu = tsf->calculateStress({-10, -20}, {1, 2});
   cout << "Stress:\n";
   cout << solu;
   auto sigma = tsf->calculateSigma();
   cout << "Sigma:\n";
   for (auto &i: sigma) {
       cout << i << endl;
   }
   ```
   其中add方法可以添加点和框架，需要先添加点(`TrussPoint`)，再添加桁架(`TrussEdge`)，点的下标从0开始，`TrussEdge(0, 1)`表示连接0号和1号结点的边
2. 可以链式调用
3. 可以快速计算应力(`calculateSigma`)和位移(`calculateStress`)

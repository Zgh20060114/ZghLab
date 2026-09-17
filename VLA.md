- vla:在 Transformer 框架基础上，根据视觉图像和自然语言的任务描述作为输入，通过理解开放语义和图像内容，计算机器人控制动作.
- llm/vlm基础上后用机器人数据训练得到的vla会出现虚假遗忘: 1.采用分层架构(vlm+action expert). 2.改进vla的训练数据.
 - vla模型架构:
  - 视觉编码器:cnn/vision transformer/vlm的视觉编码器
  - 特征推理:把视觉编码、任务描述编码、历史观测编码融合在一起，捕获它们之间的相关信息，推理出适用于预测机器人动作的特征.它是“想清楚该做什么”的阶段.
    - 扩散模型从带噪声样本预测噪声，然后去掉噪声.训练时，模型学的是“当前样本里有多少噪声”；推理时，从纯噪声开始，逐步预测并去掉噪声，最终生成干净的动作/图画.推理时根据观测和指令逐步选择一个模式。所以扩散模型能保留多模态，而 MSE 不能。
    - diffusion transformer(DiT)被称为vla的骨干网络.
    - vla中的令牌(token)是模型处理信息的基本单位，本质上是一个高维向量。图像通过 ViT 切成 patch 变成视觉令牌，语言通过分词器和嵌入层变成语言令牌，状态通过线性层变成状态令牌。所有令牌拼接后送入 Transformer 骨干，经过 Self-Attention 和 Cross-Attention 融合，输出特征令牌，用于预测机器人动作。
  - 动作解码
    - vla动作解码时采用扩散策略或者流匹配,来实现连续动作空间的生成,在连续动作空间中生成动作,实现多模态动作分布.
- vla后训练方法: 1.监督微调,2.强化微调,3.推理扩展.
- incorporaiton 结合
- recede 滚动, receding horizon control 滚动时域控制.(和mpc的思路一致)
- conditioning 条件化, visual conditioning 视觉条件化.
- diffusion 扩散, time-series diffusion 时间序列扩散.
- imitation 模仿, imitation learning 模仿学习.
- visuomotor policy 视觉运动策略.
- formulate 表述.
- supervised regression task 监督回归任务.
- nature 性质,特性.
- multimodal distribution 多模态分布.
- correlation 相关性.
$$
\mathbf{x}^k = \sqrt{\bar{\alpha}_k} \, \mathbf{x}^0 + \sqrt{1 - \bar{\alpha}_k} \, \epsilon
$$
- 论文特意强调一个设计抉择:扩散建模的是条件分布p(At | Ot)，而不是先前规划类
工作（Diffuser）建模的联合分布p(At, Ot), 这个就是"视觉条件化",把视觉输入当作是一个条件.
- “嵌入”（Embedding）这个词来自数学中的嵌入（Embedding） 概念，意思是：把一个对象映射到另一个空间里，并保留它有意义的结构.在深度学习中，“嵌入”通常指：把离散的、高维的、或不同格式的数据，映射成连续的、低维的、统一的向量表示.
- dp模型训练时输出的是噪声预测,推理时输出的是动作序列.
$$
\mathbf{A}_t^{k-1} = \alpha \left( \mathbf{A}_t^k - \gamma \, \epsilon_{\theta}\left( \mathbf{O}_t, \mathbf{A}_t^k, k \right) + \mathcal{N}\left( \mathbf{0}, \sigma^2 \mathbf{I} \right) \right)
$$
- 推理中的去噪过程.
- dp关键设计:
  - cnn/transformer架构的去噪网络
  - 把视觉编码器的resnet18骨干网络中的全局平均池化换成空间软最大池化,batchnorm换成groupnorm,训练时使用指数移动平均ema技巧
  - 噪声调度
  - 推理加速:训练照常用100 步学，推理时跳步只用10 步采样.
- 相机的手眼标定:求出相机和机器人末端（或基座）之间的相对位置和姿态关系.
- ee: end effector 末端执行器.
- SE(3) 是数学里的一个概念,全称是 Special Euclidean Group in 3D(三维特殊欧几里得群).在机器人学里，它用来表示三维空间中的刚体变换.简单说:SE(3) 就是一个 4×4 的矩阵，能同时描述“旋转”和“平移”.
- umi推理时的输入:
  - 最近几帧的gopro图像
  - 夹爪(ee)当前位姿与上一帧位姿的增量.
- umi推理时的输出:
  - 

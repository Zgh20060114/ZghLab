import torch
import torch.nn as nn
import random
from collections import deque


# 1. Q 网络
class QNetwork(nn.Module):
    def __init__(self, state_dim, action_dim):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(state_dim, 128),
            nn.ReLU(),
            nn.Linear(128, 128),
            nn.ReLU(),
            nn.Linear(128, action_dim),
        )

    def forward(self, s):
        return self.net(s)


# 2. 经验回放缓冲区
class ReplayBuffer:
    def __init__(self, capacity):
        self.buffer = deque(maxlen=capacity)

    def push(self, s, a, r, s_next, done):
        self.buffer.append((s, a, r, s_next, done))

    def sample(self, batch_size):
        batch = random.sample(self.buffer, batch_size)
        return zip(*batch)


# 3. DQN 智能体
class DQNAgent:
    def __init__(self, state_dim, action_dim, lr=1e-3, gamma=0.99, epsilon=0.1):
        self.q_net = QNetwork(state_dim, action_dim)
        self.target_net = QNetwork(state_dim, action_dim)
        self.target_net.load_state_dict(self.q_net.state_dict())  # 同步
        self.optimizer = torch.optim.Adam(self.q_net.parameters(), lr=lr)
        self.buffer = ReplayBuffer(10000)
        self.gamma = gamma
        self.epsilon = epsilon
        self.action_dim = action_dim

    def act(self, s):
        if random.random() < self.epsilon:
            return random.randrange(self.action_dim)
        with torch.no_grad():
            return self.q_net(torch.FloatTensor(s)).argmax().item()

    def learn(self, batch_size=64):
        if len(self.buffer.buffer) < batch_size:
            return
        s, a, r, s_next, done = self.buffer.sample(batch_size)
        s = torch.FloatTensor(s)
        a = torch.LongTensor(a).unsqueeze(1)
        r = torch.FloatTensor(r)
        s_next = torch.FloatTensor(s_next)
        done = torch.FloatTensor(done)

        # 计算 TD 目标（用目标网络）
        q_next = self.target_net(s_next).max(1)[0].detach()
        target = r + self.gamma * q_next * (1 - done)

        # 计算当前 Q 值
        q = self.q_net(s).gather(1, a).squeeze()

        # 损失
        loss = nn.MSELoss()(q, target)

        # 梯度下降
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

    def update_target(self):
        self.target_net.load_state_dict(self.q_net.state_dict())


# 创建环境
env = gym.make("CartPole-v1")
state_dim = env.observation_space.shape[0]
action_dim = env.action_space.n

agent = DQNAgent(state_dim, action_dim)

for episode in range(500):
    s = env.reset()
    done = False
    ep_reward = 0

    while not done:
        # 动作选择（调用 act）
        a = agent.act(s)
        s_next, r, done, _ = env.step(a)
        ep_reward += r

        # 存储
        agent.buffer.push(s, a, r, s_next, done)

        # 学习
        agent.learn()

        s = s_next

    # 每 10 个 episode 更新目标网络
    if episode % 10 == 0:
        agent.update_target()

    print(f"Episode {episode}, Reward: {ep_reward}")

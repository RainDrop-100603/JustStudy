import torch
import torchvision
import torchvision.transforms as transforms
import torch.nn as nn
import torch.optim as optim

device = "cuda" if torch.cuda.is_available() else "cpu"
torch.manual_seed(777)
if device == "cuda":
    print("cuda avaliable")
    torch.cuda.manual_seed_all(777)

# transform.Compose: data를 원하는 형태로 가공
# normalize: (value-mean)/std, 3ch(rgb)라 3개, 0~1을 -1~1로 바꿈, transforms.Normalize((mean1, mean2, mean3), (std1, std2, std3)),
transform = transforms.Compose([transforms.ToTensor(), transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])

batch_size = 100
num_workers = 8  # cpu 사용량, 스레드의 절반 정도면 무난하다.

trainset = torchvision.datasets.CIFAR10(root="./data", train=True, download=True, transform=transform)
trainloader = torch.utils.data.DataLoader(
    trainset, batch_size=batch_size, shuffle=True, num_workers=num_workers, drop_last=True
)

testset = torchvision.datasets.CIFAR10(root="./data", train=False, download=True, transform=transform)
testloader = torch.utils.data.DataLoader(
    testset, batch_size=batch_size, shuffle=False, num_workers=num_workers, drop_last=True
)

classes = ("plane", "car", "bird", "cat", "deer", "dog", "frog", "horse", "ship", "truck")

print(testset[0][0].size())

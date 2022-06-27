import torch
import torchvision
import torchvision.transforms as transforms
import torch.nn.init


class CNN(torch.nn.Module):
    def __init__(self):
        super(CNN, self).__init__()
        self.layer1 = torch.nn.Sequential(
            torch.nn.Conv2d(1, 32, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(),
            torch.nn.MaxPool2d(kernel_size=2, stride=2),
        )
        self.layer2 = torch.nn.Sequential(
            torch.nn.Conv2d(32, 64, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(),
            torch.nn.MaxPool2d(kernel_size=2, stride=2),
        )
        self.fc = torch.nn.Linear(7 * 7 * 64, 10, bias=True)
        torch.nn.init.xavier_uniform_(self.fc.weight)  # 가중치 초기화 방식

    def forward(self, x):
        out = self.layer1(x)
        out = self.layer2(out)
        out = out.view(out.size(0), -1)  # flatten
        out = self.fc(out)
        return out


def main():

    device = "cuda" if torch.cuda.is_available() else "cpu"
    torch.manual_seed(777)
    if device == "cuda":
        print("cuda avaliable")
        torch.cuda.manual_seed_all(777)

    # Hyper parameters
    batch_size = 256
    training_epochs = 15
    learning_rate = 0.001
    num_workers = 4  # cpu 사용량, 스레드의 절반 정도면 무난하다.

    # dataset, drop_last: 딱 떨어지지 않는 batch는 안씀
    mnist_train = torchvision.datasets.MNIST(root="./data", train=True, transform=transforms.ToTensor(), download=True)
    mnist_test = torchvision.datasets.MNIST(root="./data", train=False, transform=transforms.ToTensor(), download=True)
    data_loader = torch.utils.data.DataLoader(
        dataset=mnist_train, batch_size=batch_size, shuffle=True, drop_last=True, num_workers=num_workers
    )

    model = CNN().to(device)
    criterion = torch.nn.CrossEntropyLoss().to(device)  # softmax 포함되어 있음
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
    total_batch = len(data_loader)
    print(f"총 배치의 수: {total_batch}")

    for epoch in range(training_epochs):
        avg_cost = 0

        for X, Y in data_loader:  # 미니 배치 단위로 꺼내온다, X = 미니배치, Y = label
            # image is already size of 28x28, no reshape
            # label is not one-hot encoded
            X = X.to(device)
            Y = Y.to(device)

            optimizer.zero_grad()
            hypothesis = model(X)
            cost = criterion(hypothesis, Y)
            cost.backward()
            optimizer.step()

            avg_cost += cost / total_batch

        with torch.no_grad():
            X_test = mnist_test.test_data.view(len(mnist_test), 1, 28, 28).float().to(device)
            Y_test = mnist_test.test_labels.to(device)

            prediction = model(X_test)
            correct_prediction = torch.argmax(prediction, 1) == Y_test
            accuracy = correct_prediction.float().mean()

        print(f"[Epoch: {epoch+1:>4}] cost = {avg_cost:>.9} test_accuracy = {accuracy.item():>.9}")

    # test


if __name__ == "__main__":
    main()

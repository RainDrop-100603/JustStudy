import torch
import torchvision
import torchvision.transforms as transforms


class CNN3(torch.nn.Module):
    def __init__(self):
        super(CNN3, self).__init__()
        # 3 32 32 -> 64 16 16, conv layer
        self.layer1 = torch.nn.Sequential(
            torch.nn.Conv2d(3, 64, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(),
            torch.nn.MaxPool2d(kernel_size=2, stride=2),
        )
        # 64 16 16 -> 128 8 8, conv layer
        self.layer2 = torch.nn.Sequential(
            torch.nn.Conv2d(64, 128, kernel_size=3, stride=1, padding=1),
            torch.nn.ReLU(),
            torch.nn.MaxPool2d(kernel_size=2, stride=2),
        )
        self.fc1 = torch.nn.Linear(8 * 8 * 128, 512, bias=True)  # fully connected layer
        self.fc2 = torch.nn.Linear(512, 10, bias=True)  # fully connected layer
        self.dropout = torch.nn.Dropout(0.25)  # dropout for fc layer
        torch.nn.init.xavier_uniform_(self.fc1.weight)  # 가중치 초기화 방식

    def forward(self, x):
        # 전체적인 설명: 3채널 32x32 이미지를 conv-layer을 통해 특징을 추출하여, 64채널 16x16, 128채널 8x8로 간소화, 특징 추출
        # 2개의 fully connected layer를 사용하며, 각 layer에 25% dropout을 적용
        out = self.layer1(x)
        out = self.layer2(out)
        out = out.view(out.size(0), -1)  # flatten
        out = self.dropout(out)
        out = torch.nn.functional.relu(self.fc1(out))
        out = self.dropout(out)
        out = self.fc2(out)

        return out


def train_model(device, train_loader, validation_loader, learning_rate, training_epochs, model_name):
    # 모델 및 학습방법 정의
    model = CNN3().to(device)
    criterion = torch.nn.CrossEntropyLoss().to(device)  # softmax 포함되어 있음
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)

    total_batch = len(train_loader)
    validation_len = len(validation_loader)
    for epoch in range(training_epochs):
        # 학습
        avg_cost = 0
        for X, Y in train_loader:  # 미니 배치 단위로 꺼내온다, X = 미니배치, Y = label
            X = X.to(device)
            Y = Y.to(device)

            optimizer.zero_grad()
            hypothesis = model(X)
            cost = criterion(hypothesis, Y)
            cost.backward()
            optimizer.step()

            avg_cost += cost / total_batch
        # validation data 검증
        with torch.no_grad():
            avg_accuracy = 0
            for x, y in validation_loader:
                x_test = x.to(device)
                y_test = y.to(device)
                prediction = model(x_test)
                correct_prediction = torch.argmax(prediction, 1) == y_test
                avg_accuracy += correct_prediction.float().mean()
            avg_accuracy = avg_accuracy / validation_len
            print(f"[Epoch: {epoch+1:>4}] cost = {avg_cost:>.9} validation_accuracy = {avg_accuracy:>.9}")

    torch.save(model.state_dict(), f"./data/{model_name}.pt")


def run_model(device, test_loader, model_name):
    model = CNN3().to(device)
    model.load_state_dict(torch.load(f"./data/{model_name}.pt"))
    model.eval()
    test_len = len(test_loader)
    with torch.no_grad():
        avg_accuracy = 0
        for x, y in test_loader:
            x_test = x.to(device)
            y_test = y.to(device)
            prediction = model(x_test)
            correct_prediction = torch.argmax(prediction, 1) == y_test
            avg_accuracy += correct_prediction.float().mean()
        avg_accuracy = avg_accuracy / test_len
        print(f"test_accuracy = {avg_accuracy:>.9}")


def get_data(batch_size, num_workers):
    # train, validation, test dataset
    # classes = ("plane", "car", "bird", "cat", "deer", "dog", "frog", "horse", "ship", "truck")

    # transform.Compose: data를 원하는 형태로 가공
    # normalize: (value-mean)/std, 3ch(rgb)라 3개, 0~1을 -1~1로 바꿈, transforms.Normalize((mean1, mean2, mean3), (std1, std2, std3)),
    transform = transforms.Compose([transforms.ToTensor(), transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])

    # train and validation set, validation set은 early stopping, hyper parameter 선택에 사용
    tmp_set = torchvision.datasets.CIFAR10(root="./data", train=True, download=True, transform=transform)
    train_len = int(len(tmp_set) * 0.9)
    val_len = len(tmp_set) - train_len
    train_set, validation_set = torch.utils.data.random_split(tmp_set, [train_len, val_len])
    train_loader = torch.utils.data.DataLoader(
        train_set, batch_size=batch_size, shuffle=True, num_workers=num_workers, drop_last=True
    )
    validation_loader = train_loader = torch.utils.data.DataLoader(
        validation_set, batch_size=batch_size, shuffle=False, num_workers=num_workers, drop_last=True
    )

    # test set
    test_set = torchvision.datasets.CIFAR10(root="./data", train=False, download=True, transform=transform)
    test_loader = train_loader = torch.utils.data.DataLoader(
        test_set, batch_size=batch_size, shuffle=False, num_workers=num_workers, drop_last=True
    )

    return train_loader, validation_loader, test_loader


def main():
    # device setup
    device = "cuda" if torch.cuda.is_available() else "cpu"
    torch.manual_seed(777)
    if device == "cuda":
        print("cuda avaliable")
        torch.cuda.manual_seed_all(777)

    # hyper parameter
    num_workers = 4  # 멀티태스킹, 오류 안나는 선에서 적당히
    batch_size = 256
    learning_rate = 0.001
    training_epochs = 30
    model_name = "cnn3_256_001_30"

    # run
    print(model_name)
    train_loader, validation_loader, test_loader = get_data(batch_size, num_workers)  # model 불러오기
    train_model(device, train_loader, validation_loader, learning_rate, training_epochs, model_name)  # model train
    run_model(device, test_loader, model_name)  # test data로 실행


if __name__ == "__main__":
    # 멀티태스킹 오류 안나려면 이렇게 실행해야 한다
    main()

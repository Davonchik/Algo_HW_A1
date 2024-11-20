import matplotlib.pyplot as plt

with open("big_square.txt", "r") as f:
    big_square_data = [l.split() for l in f.readlines()]

with open("small_square.txt", "r") as f:
    small_square_data = [l.split() for l in f.readlines()]

def build_plots(big_square_data, small_square_data):
    x_mas = [int(x) for x, y1, y2 in big_square_data]

    y1_big = [float(y1) for x, y1, y2 in big_square_data]
    y2_big = [float(y2) for x, y1, y2 in big_square_data]

    y1_small = [float(y1) for x, y1, y2 in small_square_data]
    y2_small = [float(y2) for x, y1, y2 in small_square_data]

    plt.figure(figsize=(15, 10))
    plt.plot(x_mas, [0.944517] * len(x_mas), label="Real Area", alpha=0.8, color="red")
    plt.plot(x_mas, y1_big, label="Big Square")
    plt.plot(x_mas, y1_small, label="Small Square")
    plt.scatter(x_mas, y1_big, label="points 1", s=15, alpha=0.5)
    plt.scatter(x_mas, y1_small, label="points 2", s=15, alpha=0.5)
    plt.xlabel("point count")
    plt.ylabel("square value")
    plt.legend()
    plt.grid()
    plt.title("First Type Plot (Dependence of the approximate area on the number of pointsN)")
    plt.savefig("first_type_plot.png")

    plt.figure(figsize=(15, 10))
    plt.plot(x_mas, y2_big, label="Big Square")
    plt.plot(x_mas, y2_small, label="Small Square")
    plt.scatter(x_mas, y2_big, label="points 1", s=15, alpha=0.5)
    plt.scatter(x_mas, y2_small, label="points 2", s=15, alpha=0.5)
    plt.xlabel("point count")
    plt.ylabel("relative error")
    plt.legend()
    plt.grid()
    plt.title("Second Type Plot (Relative Deviation Graph)")
    plt.savefig("second_type_plot.png")

build_plots(big_square_data, small_square_data)
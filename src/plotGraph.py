# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
from sys import argv


if __name__ == '__main__':
    source, read_file = argv
    graphF = open(read_file)            #  ファイルのオープン
    graph = list()                      # 空のリスト作成

    for color, numOfColor in enumerate(graphF):
        numOfColor.rstrip()        # 改行文字を取り出す
        graph.append(int(numOfColor))   # 要素の追加
        #graph.append([color, int(numOfColor)])
    graphF.close()      # フアイルのクローズ

#    print(graph)
    x = np.arange(0, len(graph), 1) # x軸
    y = np.array(graph)             # y軸

    plt.title("kadai")
    plt.xlabel("color")
    plt.ylabel("pixels")
    plt.plot(x, y)
    plt.show()                       # グラフにして出力

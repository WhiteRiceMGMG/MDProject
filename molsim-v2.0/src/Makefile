# コンパイラとフラグ
CC = gcc
CFLAGS = -Wall -O2 -std=c99

# ソースファイルとオブジェクトファイル
SRCS = main.c atom.c force.c integrator.c
OBJS = $(SRCS:.c=.o)

# ヘッダーファイル
HEADERS = atom.h force.h integrator.h parameter.h sysdef.h

# 出力ファイル名
TARGET = main

# デフォルトターゲット
all: $(TARGET)

# リンクして実行ファイルを作成
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 依存関係のある.oファイルの生成ルール
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンアップ
clean:
	rm -f $(OBJS) $(TARGET)

# 再ビルド
rebuild: clean all

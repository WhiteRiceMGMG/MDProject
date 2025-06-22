# コンパイラとフラグ
CC = gcc
CFLAGS = -Wall -O2 -std=c99
LDFLAGS = -lm  # 数学関数用のリンクオプション

# ソースファイルとオブジェクトファイル
SRCS = main.c atom.c force.c integrator.c boundary.c output.c sysmsg.c temperature.c initialAtom.c
OBJS = $(SRCS:.c=.o)

# ヘッダーファイル（依存関係リスト）
HEADERS = atom.h force.h integrator.h parameter.h sysdef.h boundary.h output.h sysmsg.h temperature.h initialAtom.h

# 出力ファイル名
TARGET = main

# デフォルトターゲット
all: $(TARGET)

# リンクして実行ファイルを作成
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# 依存関係のある.oファイルの生成ルール
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンアップ
clean:
	rm -f $(OBJS) $(TARGET)

# 再ビルド
rebuild: clean all
	@echo "全て再ビルドが完了しました！✨"

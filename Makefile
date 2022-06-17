SHELL := /bin/bash # Use bash syntax
.PHONY: clean test judge1 judge2 judge3 help
.DEFAULT: help

help:
	@echo "make judge1: judge with bot 1"
	@echo "make judge2: judge with bot 2"
	@echo "make judge3: judge with bot 3"
	@echo "make test: test player with sample input"
	@echo "make clean: clean generate files"

clean:
	@rm -rf tmp
	@rm -rf *.log

test:
	@mkdir tmp
	@cp player/player.cpp tmp/player.cpp
	@g++ tmp/player.cpp -o tmp/player
	@echo "test player with sampleA.in"
	@timeout 1 tmp/player < sample/sampleA.in
	@echo "test player with sampleB.in"
	@timeout 1 tmp/player < sample/sampleB.in
	@echo "test pass"
	@rm -rf tmp

judge1:
	@mkdir tmp
	@cp judge/judge.py tmp
	@cp map/88map tmp
	@echo "player be A, bot1 be B"
	@cp player/player.cpp tmp/A.cpp
	@cp bot/bot1.cpp tmp/B.cpp
	@g++ tmp/A.cpp -o tmp/A
	@g++ -std=c++11 tmp/B.cpp -o tmp/B
	@cd tmp && python3 judge.py
	@cp tmp/move.log move_player_be_A.log
	@rm tmp/*.log
	@echo "bot1 be A, player be B"
	@cp player/player.cpp tmp/B.cpp
	@cp bot/bot1.cpp tmp/A.cpp
	@g++ -std=c++11 tmp/A.cpp -o tmp/A
	@g++ tmp/B.cpp -o tmp/B
	@cd tmp && python3 judge.py
	@cp tmp/move.log move_player_be_B.log
	@rm -rf tmp

judge2:
	@mkdir tmp
	@cp judge/judge.py tmp
	@cp map/88map tmp
	@echo "player be A, bot2 be B"
	@cp player/player.cpp tmp/A.cpp
	@cp bot/bot2.cpp tmp/B.cpp
	@g++ tmp/A.cpp -o tmp/A
	@g++ -std=c++11 tmp/B.cpp -o tmp/B
	@cd tmp && python3 judge.py
	@cp tmp/move.log move_player_be_A.log
	@rm tmp/*.log
	@echo "bot2 be A, player be B"
	@cp player/player.cpp tmp/B.cpp
	@cp bot/bot2.cpp tmp/A.cpp
	@g++ -std=c++11 tmp/A.cpp -o tmp/A
	@g++ tmp/B.cpp -o tmp/B
	@cd tmp && python3 judge.py
	@cp tmp/move.log move_player_be_B.log
	@rm -rf tmp

judge3:
	@mkdir tmp
	@cp judge/judge.py tmp
	@cp map/88map tmp
	@echo "player be A, bot3 be B"
	@cp player/player.cpp tmp/A.cpp
	@cp bot/bot3.cpp tmp/B.cpp
	@g++ tmp/A.cpp -o tmp/A
	@g++ -std=c++11 -w tmp/B.cpp -o tmp/B
	@cd tmp && python3 judge.py
	@cp tmp/move.log move_player_be_A.log
	@rm tmp/*.log
	@echo "bot3 be A, player be B"
	@cp player/player.cpp tmp/B.cpp
	@cp bot/bot3.cpp tmp/A.cpp
	@g++ -std=c++11 -w tmp/A.cpp -o tmp/A
	@g++ tmp/B.cpp -o tmp/B
	@cd tmp && python3 judge.py
	@cp tmp/move.log move_player_be_B.log
	@rm -rf tmp

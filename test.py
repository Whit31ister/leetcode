import random


class Player:
    def __init__(self, name):
        self.name = name
        self.score = 0

    def choose_move(self):
        while True:
            move = input(f"{self.name}, choose rock, paper, or scissors: ").strip().lower()
            if move in {"rock", "paper", "scissors"}:
                return move
            print("Invalid choice. Please enter rock, paper, or scissors.")


class ComputerPlayer:
    def __init__(self, name="Computer"):
        self.name = name
        self.score = 0

    def choose_move(self):
        return random.choice(["rock", "paper", "scissors"])


class Game:
    def __init__(self):
        self.player = Player("Player")
        self.computer = ComputerPlayer()

    def determine_winner(self, player_move, computer_move):
        if player_move == computer_move:
            return "Draw"
        winning_moves = {
            "rock": "scissors",
            "paper": "rock",
            "scissors": "paper",
        }
        if winning_moves[player_move] == computer_move:
            return self.player.name
        return self.computer.name

    def play_round(self):
        player_move = self.player.choose_move()
        computer_move = self.computer.choose_move()
        print(f"You chose: {player_move}")
        print(f"Computer chose: {computer_move}")

        winner = self.determine_winner(player_move, computer_move)
        if winner == "Draw":
            print("It's a draw!")
        else:
            print(f"{winner} wins this round!")
            if winner == self.player.name:
                self.player.score += 1
            else:
                self.computer.score += 1

        print(f"Score: Player {self.player.score} - Computer {self.computer.score}\n")

    def play(self):
        print("Welcome to Rock, Paper, Scissors!")
        while True:
            self.play_round()
            again = input("Play again? (y/n): ").strip().lower()
            if again != "y":
                print("Thanks for playing!")
                break


if __name__ == "__main__":
    game = Game()
    game.play()

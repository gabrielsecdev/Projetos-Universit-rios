import json

"""
Programação por Objetos - 21093
Gabriel Pereira
nº 2301429
"""

class GameStats:
    def __init__(self, file_path="game_stats.json"):
        self.file_path = file_path
        self.data = {"Player 1 (You)": 0, "NPC": 0}  # Contagem inicial de vitórias
        self.load_data()

    def load_data(self):
        try:
            with open(self.file_path, "r") as file:
                self.data = json.load(file)
        except FileNotFoundError:
            self.save_data()  # Cria o arquivo se não existir

    def save_data(self):
        with open(self.file_path, "w") as file:
            json.dump(self.data, file)

    def record_win(self, winner_name):
        if "Player 1" in winner_name:
            self.data["Player 1 (You)"] += 1
        else:
            self.data["NPC"] += 1
        self.save_data()

    def display_stats(self):
        print("\nEstatísticas do Jogo:")
        for player, wins in self.data.items():
            print(f"{player}: {wins} vitórias")
            
import random

"""
Programação por Objetos - 21093
Gabriel Pereira
nº 2301429
"""
class Player:
    def __init__(self, name):
        self.name = name
        self.hand = []
        self.revolver = [False] * 6  # 6 chambers in the revolver
        self.current_position = 0   # Starts at position 0 (first chamber)
        self.revolver[random.randint(0, 5)] = True  # Place a bullet randomly in one chamber

    def deal_cards(self, cards):
        self.hand = cards  # Method to deal cards to the player


# Human Player class
class HumanPlayer(Player):
    def __init__(self, name):
        super().__init__(name)

    def play_cards(self, num_cards, game):
        print(f"\nVez de {self.name}. Sua mão:")
        for i, card in enumerate(self.hand, start=1):  # Display cards starting from 1
            print(f"{i}. {card}")
        print("Escolha quais cartas jogar.")
        print("Digite os índices das cartas que deseja jogar, separados por vírgulas começando pelo 1 (ex.: 1,3,4):")
        indices = input().split(',')
        indices = [int(i) - 1 for i in indices if i.strip().isdigit() and 1 <= int(i) <= len(self.hand)]  # Convert input to valid indices

        if indices:
            cards_played = [self.hand[i] for i in indices]
            self.hand = [self.hand[i] for i in range(len(self.hand)) if i not in indices]
            return cards_played
        else:
            print("Entrada inválida. Tente novamente.")
            return self.play_cards(num_cards, game)

# NPC Player class
class NPCPlayer(Player):
    def __init__(self, name):
        super().__init__(name)

    def play_cards(self, num_cards, game):
        num_cards_to_play = min(num_cards, len(self.hand))  # Determine how many cards to play
        played_cards = random.sample(self.hand, num_cards_to_play)
        self.hand = [card for card in self.hand if card not in played_cards]  # Update hand to remove played cards
        print(f"{self.name} jogou {num_cards_to_play} cartas...")
        return played_cards
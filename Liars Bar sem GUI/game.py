import random
from deck import Deck
from player import Player, HumanPlayer, NPCPlayer
from GameStats import GameStats

"""
Programação por Objetos - 21093
Gabriel Pereira
nº 2301429
"""
class Game:
    def __init__(self):
        self.deck = Deck()
        self.players = [
            HumanPlayer("Player 1 (You)"), 
            NPCPlayer("Player 2 (NPC)"),
            NPCPlayer("Player 3 (NPC)"),
            NPCPlayer("Player 4 (NPC)")
        ]
        self.table_card = random.choice([card for card in self.deck.cards if card != 'Joker'])
        self.turn = 0
        self.round = 1
        self.last_cards_played = []
        self.last_player = None
        self.stats = GameStats()

        for player in self.players:
            player.hand = self.deck.deal()

    def next_turn(self):
        self.turn = (self.turn + 1) % len(self.players)
        while not self.players[self.turn].hand:
            self.turn = (self.turn + 1) % len(self.players)
        return self.players[self.turn]
        
    # Função para perguntar ao jogador se quer chamar mentiroso
    def ask_mentiroso(self, current_player):
        while True:
            action = input(f"{current_player.name}, queres chamar mentiroso ao {self.last_player.name}? (s/n): ").lower().strip()
            if action in ['s', 'n']:
                return action == 's'
            print("Erro! Por favor, insira 's' ou 'n'.")

    # Função para verificar se as cartas jogadas são válidas
    def is_lying(self, table_card, played_cards):
        """
        Verifica se as cartas jogadas são válidas.
        As cartas são válidas se todas forem iguais à carta da mesa ou forem Jokers.
        """
        return not all(card == table_card or card == 'Joker' for card in played_cards)

    # Função para verificar se o jogador vai disparar a bala
    def check_bullet(self, player):
        bullet = player.revolver[player.current_position]
        player.current_position = (player.current_position + 1) % 6  # Avança para a próxima câmara
        return bullet

    # Função para resolver o tiroteio
    def resolve_shootout(self, player):
        print(f"{player.name} puxa o gatilho...")
        bullet = self.check_bullet(player)
        if bullet:
            print(f"{player.name} saiu bala! O jogador é eliminado!")
            return True  # Player is eliminated
        else:
            print(f"{player.name} tambor vazio, o jogador sobrevive!")
            return False  # Player survives

    def resolve_challenge(self, current_player):
        """
        Resolve o desafio de mentiroso.
        Se for mentira, o jogador anterior perde. Caso contrário, o jogador atual perde.
        """
        print(f"Cartas jogadas por {self.last_player.name}: {', '.join(self.last_cards_played)}")

        if self.is_lying(self.table_card, self.last_cards_played):
            print(f"{self.last_player.name} é mentiroso! {self.last_player.name} perdeu.")
            self.resolve_shootout(self.last_player)  # Elimina o jogador mentiroso
        else:
            print(f"{self.last_player.name} foi honesto! {current_player.name} perdeu.")
            self.resolve_shootout(current_player)  # Elimina o jogador que desafiou errado
    

    def play_round(self):
        current_player = self.players[self.turn]
        print(f"\nRonda {self.round}:")
        print(f"Carta da Mesa: {self.table_card}")
        print(f"É o turno do {current_player.name}")
        # Fim do jogo
        if current_player == self.last_player:
            print("Apenas um jogador ficou, o jogo terminou!")
            print(f"{current_player.name} ganhou!")
            self.stats.record_win(current_player.name)  # Registra a vitória
            return False

        # Desafio de mentiroso
        if self.last_cards_played:
            if current_player.name == "Player 1 (You)":
                if self.ask_mentiroso(current_player):
                    self.resolve_challenge(current_player)
                    return False
            else:
                if random.choice([True, False]):  # NPC decides randomly
                    print(f"{current_player.name} chama Mentiroso!")
                    self.resolve_challenge(current_player)
                    return False

        # Jogar cartas
        self.last_cards_played = current_player.play_cards(5, self)

        self.last_player = current_player
        self.round += 1
        self.next_turn()
        return True

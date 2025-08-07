import random

"""
Programação por Objetos - 21093
Gabriel Pereira
nº 2301429
"""

class Deck:
    def __init__(self):
        self.cards = ['Joker', 'Joker', 'Ace', 'Ace', 'Ace', 'Ace', 'Ace', 'Ace',
                      'King', 'King', 'King', 'King', 'King', 'King',
                      'Queen', 'Queen', 'Queen', 'Queen', 'Queen', 'Queen']
        random.shuffle(self.cards)

    def deal(self):
        return [self.cards.pop() for _ in range(5)]

    
"""
self.devil_card = self.assign_devil_card()  # Define a Devil Card
 def assign_devil_card(self):
 
        *
        Escolhe uma carta aleatória para se tornar a Devil Card.
        Remove a carta do baralho e a substitui por "Devil Card".
        *
        
        devil_index = random.randint(0, len(self.cards) - 1)
        devil_card = self.cards[devil_index]
        self.cards[devil_index] = "Devil Card"
        return devil_card
"""
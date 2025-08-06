from game import Game
from GameStats import GameStats

"""
Programação por Objetos - 21093
Gabriel Pereira
nº 2301429
"""

def main_menu():
    print("\nBem-vindo ao LiarsBar!")
    print("1. Jogar o jogo")
    print("2. Ver estatísticas")
    print("3. Como jogar")
    print("4. Sair")

def explain_game():
    print("Regras do jogo:")
    print("1. Cada jogador recebe 5 cartas e um revólver , sendo que um dos tambores do revolver contém uma bala aleatóriamente.")
    print("2. O objetivo do jogo é se manter vivo enquanto elimina os outros jogadores.")
    print("3. No seu turno, jogue cartas que correspondam à carta da mesa ou faça bluff. O objetivo do jogo é acabar com as suas cartas primeiro.")
    print("4.Após a primeira jogada, o jogador seguinte pode chamar a jogada do jogador anterior de 'mentiroso', se desconfiar que esse jogador está a fazer bluff.")
    print("5a. Se for provado que mentiu, esse jogador perde e tem que puxar o gatilho.")
    print("5b. Se for provado que não mentiu, quem desafiou perde e pode puxar o gatilho.")
    print("6. Se um jogador puxar o gatilho e sair bala, esse jogador é eliminado. Caso contrario, o jogo continua. O jogador que sobrar com cartas na mão perde automáticamente.")	
    print("7. O último jogador sobrevivente vence o jogo!")
    print("\nBoa sorte e não seja apanhado a mentir!\n")

def display_bar():
    print(r"""
     ____________________________________________________
    |                                                    |
    |                Bem-vindo ao LiarsBar!              |
    |                                                    |
    |____________________________________________________|
      |                                                  |
      |    O bar está lotado de jogadores sem honra!     |
      |    Escolha a sua estratégia com sabedoria.       |
      |__________________________________________________|
         ||     ||     ||     ||     ||     ||     ||
         ||     ||     ||     ||     ||     ||     ||
         ||_____||_____||_____||_____||_____||_____||
    """)

def main():
    stats = GameStats()
    display_bar()
    while True:
        main_menu()
        choice = input("Escolha uma opção: ").strip()

        if choice == "1":
            print("\nIniciando o jogo...\n")
            game = Game()
            while True:
                game_over = not game.play_round()
                if game_over:
                    stats.record_win(game.last_player.name)
                    break
            stats.display_stats()

        elif choice == "2":
            stats.display_stats()

        elif choice == "3":
            explain_game()
        
        elif choice == "4":
            print("Saindo do jogo. Até mais!")
            break

        else:
            print("Opção inválida. Tente novamente.")

if __name__ == "__main__":
    main()

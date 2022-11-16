//ANGEL EMANUEL MENDOZA REYES
//22110083
//PROGRAMACION ORIENTADA OBJETOS
//LUIS MANUEL MORALES MEDINA
//CETI COLOMOS
//PARCIAL 3
//NOVELA GRAFICA
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

struct Node {
    string imagen;
    string texto;
    Node* si;
    Node* no;
};

Node* arbol;
Node* crearNodo(string, string, Node*, Node*);
Node* crearArbolBinario();

class Game {
public:
    Game(int ancho, int alto, string titulo) {
        ventana = new RenderWindow(VideoMode(ancho, alto), titulo);
        ventana->setFramerateLimit(60);
        eventos = new Event;
        menuPrincipal = true;

        string rutas[3] = { "Images/pollitos.jpg", "Images/si.png", "Images/no.png" };
        for (int contador = 0; contador < 3; contador++) {
            texturas[contador] = new Texture;
            sprites[contador] = new Sprite;
            texturas[contador]->loadFromFile(rutas[contador]);
            sprites[contador]->setTexture(*texturas[contador], true);
        }
        sprites[0]->setPosition(250, 1);
        sprites[1]->setPosition(200, 600);
        sprites[2]->setPosition(600, 600);
        
        Font fuente;
        fuente.loadFromFile("Fonts/arial.ttf");
        texto.setFont(fuente);
        texto.setString("POLLITOS-Quieres ver esta novela grafica?");
        texto.setCharacterSize(18);
        texto.setFillColor(Color::Black);
        texto.setPosition(10, 510);

        gameLoop();
    }
    void gameLoop() {
        while (ventana->isOpen()) {
            runEvents();
            dibujar();
        }
    }
    void dibujar() {
        ventana->clear(Color::White);
        ventana->draw(*sprites[0]);
        ventana->draw(*sprites[1]);
        ventana->draw(*sprites[2]);
        ventana->draw(texto);
        ventana->display();
    }
    void runEvents() {
        while (ventana->pollEvent(*eventos)) {
            switch (eventos->type) {
            case Event::Closed:
                ventana->close();
                exit(1);
                break;
            case Event::MouseButtonPressed:
                Vector2i posicionMouse = Mouse::getPosition(*ventana);
                Vector2f posicionConvertida = ventana->mapPixelToCoords(posicionMouse);
                if (sprites[1]->getGlobalBounds().contains(posicionConvertida)) {
                    if (menuPrincipal) {
                        menuPrincipal = false;
                        arbol = crearArbolBinario();
                        texto.setString(arbol->texto);
                        texturas[0]->loadFromFile("Images/" + arbol->imagen);
                    }
                    else {
                        arbol = arbol->si;
                        texto.setString(arbol->texto);
                        texturas[0]->loadFromFile("Images/" + arbol->imagen);
                        if (arbol->si == NULL) {
                            menuPrincipal = true;
                            texto.setString(arbol->texto + "\nDeseas volver a jugar?");
                        }
                    }
                }
                else if (sprites[2]->getGlobalBounds().contains(posicionConvertida)) {
                    if (menuPrincipal) {
                        ventana->close();
                        exit(1);
                    }
                    else {
                        arbol = arbol->no;
                        texto.setString(arbol->texto);
                        texturas[0]->loadFromFile("Images/" + arbol->imagen);
                        if (arbol->no == NULL) {
                            menuPrincipal = true;
                            texto.setString(arbol->texto + "\nDeseas volver a jugar?");
                        }
                    }
                }
                break;
            }
        }
    }

private:
    bool menuPrincipal;
    Text texto;
    RenderWindow* ventana;
    Texture* texturas[3];
    Sprite* sprites[3];
    Event* eventos;
};

int main() {
    Game* game = new Game(1000, 800, "Pollitos");
}

Node* crearArbolBinario() {
    Node* node5 = crearNodo("caminando.png", "Los pollitos siguen caminando y platicando entre ellos", NULL, NULL);
    Node* node4 = crearNodo("atropellado.png", "El pollito muere atropellado por querer obtener la comida", NULL, NULL);
    Node* node3 = crearNodo("comiendo.png", "Los pollitos ignoran la puerta y siguen comiendo", NULL, NULL);
    Node* node2 = crearNodo("caminando.png", "Tocaba un amigo pollito, se van de paseo por la calle y ves comida al otro lado de la calle, deseas ir por ella?", node4, node5);
    Node* node1 = crearNodo("comiendo.png", "Dos pollitos se encuentran comiendo y tocan la puerta, deseas abrir?", node2, node3);
    return node1;
}

Node* crearNodo(string imagen, string texto, Node* si, Node* no) {
    Node* node = new Node();
    node->imagen = imagen;
    node->texto = texto;
    node->no = no;
    node->si = si;
    return node;
}
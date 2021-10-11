#define SFML_STATIC
#include <SFML/Graphics.hpp>

int main()
{
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Silnik Graficzny", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    sf::RectangleShape rectangle(sf::Vector2f(200.0f,200.0f));

    sf::CircleShape triangle(100.0f, 3);

    sf::ConvexShape convex;
    convex.setPointCount(3);
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            // Close window: exit
            if (evnt.type == evnt.Closed)
                window.close();
        }
        // Clear screen
        window.clear(sf::Color::Blue);

        triangle.setPosition(300.0f,250.0f);
        rectangle.setPosition(100.0f, 50.0f);
        triangle.setFillColor(sf::Color(50,150,250));
        rectangle.setFillColor(sf::Color(150,50,250));

        convex.setPoint(0, sf::Vector2f(100.0f, 100.0f));
        convex.setPoint(1, sf::Vector2f(200.0f, 100.0f));
        convex.setPoint(2, sf::Vector2f(150.0f, 150.0f));

        // Update the window
        window.draw(rectangle);
        window.draw(triangle);
        window.draw(convex);

        window.display();
    }
    return EXIT_SUCCESS;
}
// gui.cpp
// This file implements a simple GUI for the Lotto 6/49 simulator using SFML.
//Template used not coded
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <numeric>
#include <algorithm>
#include <random>
#include "lotto.h"
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(700, 600), "Lotto 6/49 Simulator");

    sf::Font font;
    // Windows font path (MSYS2/MinGW)
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        return -1;
    }

    const int COLS = 7;
    const float CELL = 70.f, MARGIN = 50.f;
    set<int> selected;
    string resultText = "Select 6 numbers, then click Simulate";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                float mx = (float)event.mouseButton.x;
                float my = (float)event.mouseButton.y;

                // Check grid clicks
                for (int i = 0; i < 49; i++) {
                    int col = i % COLS, row = i / COLS;
                    float x = MARGIN + col * CELL;
                    float y = MARGIN + row * CELL;
                    if (mx >= x && mx < x + CELL - 5 &&
                        my >= y && my < y + CELL - 5) {
                        int num = i + 1;
                        if (selected.count(num)) selected.erase(num);
                        else if (selected.size() < 6) selected.insert(num);
                    }
                }

                // Simulate button click
                if (mx >= 250 && mx <= 450 && my >= 530 && my <= 570 && selected.size() == 6) {
                    vector<int> userNums(selected.begin(), selected.end());
                    map<int, int> results;
                    int sims = 10000;
                    for (int i = 0; i < sims; i++) {
                        auto draw = generateDraw();
                        results[countMatches(userNums, draw)]++;
                    }
                    resultText = "";
                    for (auto& [m, c] : results)
                        resultText += to_string(m) + " matches: " +
                                      to_string((int)(100.0 * c / sims)) + "%  ";
                }
            }
        }

        window.clear(sf::Color(20, 20, 40));

        // Draw number grid
        for (int i = 0; i < 49; i++) {
            int col = i % COLS, row = i / COLS;
            float x = MARGIN + col * CELL;
            float y = MARGIN + row * CELL;

            sf::RectangleShape cell(sf::Vector2f(CELL - 5, CELL - 5));
            cell.setPosition(x, y);
            cell.setFillColor(selected.count(i + 1) ? sf::Color(255, 200, 0) : sf::Color(60, 60, 100));
            window.draw(cell);

            sf::Text label(to_string(i + 1), font, 18);
            label.setPosition(x + 15, y + 15);
            label.setFillColor(sf::Color::White);
            window.draw(label);
        }

        // Simulate button
        sf::RectangleShape btn(sf::Vector2f(200, 40));
        btn.setPosition(250, 530);
        btn.setFillColor(selected.size() == 6 ? sf::Color(0, 180, 80) : sf::Color(80, 80, 80));
        window.draw(btn);

        sf::Text btnLabel("Simulate", font, 20);
        btnLabel.setPosition(310, 537);
        btnLabel.setFillColor(sf::Color::White);
        window.draw(btnLabel);

        // Results text
        sf::Text result(resultText, font, 13);
        result.setPosition(20, 580);
        result.setFillColor(sf::Color::Yellow);
        window.draw(result);

        window.display();
    }
    return 0;
}
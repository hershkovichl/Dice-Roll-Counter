#pragma once

class Graph {
	sf::RenderWindow& window;
	std::vector<int>* data;

public:
	struct bar : public sf::RectangleShape {// This class is public so that vector class can access it
		int index;
		int frequency;

		sf::Text indexLabel;
		sf::Text frequencyLabel;

		bar(int _index, int _frequency); // constructor
		static int maxFrequency;
		static int numberOfBars;
		static float outlineWidth;
		static int pixelHeightPerPoint;
	};

	static sf::Font font;

	std::vector<bar> Bars;
	const float MaxBarHeightRatio = 0.9; // Maximum ratio of the window height that a bar can reach
	sf::RectangleShape background;

	sf::Text totalRollsLabel;

	void Draw();
	void DrawBars();
	void DrawTotalRollsLabel();

	void addPoint(int index);


	void LoadData(std::vector<int>& _data);
	void MakeBars();
	void SetBarAesthetics();
	void ReduceBarHeights();


	int GetDataSize() { return data->size(); }

	void SetBarHeights(); // WIP
	Graph(sf::RenderWindow& window);
};


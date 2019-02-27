using namespace std;
using namespace sf;
class Readfile
{
protected:
	string filename;
	char expression[400];
	fstream file;
	Texture texture;
	Sprite sprite;
	RenderWindow window;
	Font font;
	Text text;
	Event event;
public:
	void read(string a, string b)
	{
		filename = a;
		file.open(filename, ios::in);
		file.get(expression, 400, '$');
		file.close();
		window.create(VideoMode(726, 600), b);
		window.setPosition(Vector2i(300, 0));
		texture.loadFromFile("back1.jpg");
		sprite.setTexture(texture);
		font.loadFromFile("tt.ttf");
		text.setFont(font);
		text.setPosition(60, 60);
		text.setCharacterSize(40);
		/*text.setLineSpacing(1.3);
		text.setLetterSpacing(0.2);/**/
		text.setFillColor(Color::Black);
		text.setString(expression);
		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if(event.type== Event::Closed)
				{
				
					window.close();
					
			
				}
			}
			window.clear();
			window.draw(sprite);
			window.draw(text);
			window.display();
		}
	}
};

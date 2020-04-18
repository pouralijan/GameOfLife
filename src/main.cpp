#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
#include <unistd.h>
//#include <algorithm>

using namespace std;

class Point 
{
	public:
		int x;
		int y;
		Point(){}
		Point(int x, int y)
		{
			this->x = x;
			this->y = y;
		}
		string get_key() const
		{
			return to_string(this->x) + ":" + to_string(this->y);
		}

		bool operator<(const Point& point) const
		{
			if(x < point.x) return true;
			if(x == point.x && y < point.y) return true;
			return false;
		}

		bool operator==(const Point& point) const
		{
			//return get_key() == point.get_key();
			return (x == point.x && y == point.y);
		}
};

class Size : public Point 
{
	public:
		Size(){}
		Size(int x, int y): Point(x, y)
		{
		}
};

class Crearue
{
	public:
		Point point;
		Crearue(Point point, bool alive)
		{
			this->point = point;
			this->alive = alive;
		}
		bool alive = false;
		void revive(bool alive)
		{
			this->alive = alive;
		};
		bool is_alive()
		{
			return alive;
		}
		string stat()
		{
			return is_alive() ? "#" : " ";
		}
};

class World
{
	public:
		map<Point, Crearue> crearues;
		Size world_size;
		int evol = 0;
		World(Size world_size)
		{
			srand (time(NULL));
			this->world_size = world_size;
			for(int i=0; i < this->world_size.x; i++)
				for(int j=0; j < this->world_size.y; j++)
					this->crearues.insert(pair<Point, Crearue>(Point(i,j), Crearue(Point(i, j),
									rand() < RAND_MAX / 10 ? true : false)));
			drow();
		}
		void drow()
		{
			system("clear");
			cout << "|";
			for(int i =0; i < world_size.y; i++)
				cout << "-";
			cout << "|" << endl << "|";
			for (auto c : this->crearues)
			{
				cout << c.second.stat();
				if(c.second.point.y == this->world_size.y -1)
					cout << "|" << endl << "|";
			}
			
			for(int i =0; i < world_size.y; i++)
				cout << "-";
			cout << "|";
			cout << endl << "Evolution: " << evol << endl ;
			evol++;
		}
		void evolution()
		{
			// 
			//       ***    (x-1, y-1) (x, y-1) (x+1, y-1)
			//       *.*    (x-1, y)   (x, y)   (x+1, y)
			//       ***    (x-1, y+1) (x, y+1) (x+1, y+1)
			//       
			for (auto& c : this->crearues)
			{
				int live =0;
				for(int x = c.second.point.x - 1; x <= c.second.point.x + 1; x++)
				{
					for(int y = c.second.point.y - 1; y <= c.second.point.y + 1; y++)
					{
						Point neighbor_point(x + world_size.x % world_size.x,y+world_size.y % world_size.y);
						auto neighbor = crearues.find(neighbor_point);
						if(neighbor != crearues.end())
							if(neighbor->second.is_alive())
								live++;
					}
				}
				if(c.second.is_alive()) live--;
				c.second.revive((live == 3  || (live == 2 && c.second.is_alive())));
			}
		}
};

int main()
{
	World w(Size(30, 90));
	while(true)
	{
		w.drow();
		w.evolution();
		usleep(1000000);
	}
}


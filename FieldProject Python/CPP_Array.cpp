#include <iostream>         //Imports
#include <String>
#include <fstream>
using namespace std;

int main()  //Main code
{
    string name;        //Variables
    int x, y, temp1;
    cout << "\nEnter filename : ";      //Input file name from User
    cin >> name;
    ifstream file(name);        //Open the file for reading data
    file >> x;          //Read the Width of field from first line of file   
    file >> y;          //Read the height of field from file
    int map[x][y];      //Create 2 maps. 1 for storing data and second for updating data
    int map1[x][y];
    for (int i = 0; i < x; i++)     //Initialize both arrays to zero so no garbage value appears
    {
        for (int j = 0; j < y; j++)
        {
            map[i][j] = 0;
            map1[i][j] = 0;     //Gettinf rid of garbage values
        }
    }
    int year = 1;
    while (file >> temp1)   // Loop executes until end of file is reached
    {
        int count = 0;      // Read how many data entries are present in each year
        file >> count;
        for (int var1 = 0; var1 < count; var1++)    //Enter data to map
        {
            int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
            file >> x1;     //Read first x axis
            file >> y1;     //Read first y axis
            file >> x2;     //Read second x axis
            file >> y2;     //Read second Y axis
            for (int i = 0; i < x; i++)         //Nested loop to write data
            {
                for (int j = 0; j < y; j++)
                {
                    if ((i >= x1 && i <= x2) && (j >= y1 && j <= y2))     //If in range of provided cordinates
                    {
                        map[i][j] += 1;     //Update the data value by adding 1.
                    }
                }
            }
        }
        for (int i = 0; i < x; i++)     //Nested loops for updating values of maps
        {
            for (int j = 0; j < y; j++)
            {
                if (map[i][j] == 0 && map1[i][j] > 0)   //Compares both maps and reduce value of unused places
                    map1[i][j]--;
                else if (map[i][j] > 0 && map1[i][j] >= 0) //Compares and increase value of used places
                    map1[i][j]++;
            }
        }
        if (year == 1)      //So next loops execute only after first year data read
        {
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++)
                {
                    map1[i][j] = map[i][j];     //Copy data to temporary map
                }
            }
        }
        for (int i = 0; i < x; i++)
        {
            for (int j = 0; j < y; j++)
            {
                map[i][j] = 0;  //Clear map to read values of next year
            }
        }
        year++;
    }
    //The output until here is tranposed se we have to take transpose of matrix to restore it in correct form
    int transpose[x][y];        //Temporary array
    for (int i = 0; i < x; ++i)
        for (int j = 0; j < y; ++j)
        {
            transpose[j][i] = map1[i][j];   //Simply give value of rows to coloums of other matrix
        }

    for (int i = 0; i < y; ++i)
        for (int j = 0; j < x; ++j)
        {
            cout << " " << transpose[i][j]; //Finally printing the output
            if (j == x - 1)
                cout << endl;
        }
    file.close();   //Closing the file before quiting program
    return 0;
}

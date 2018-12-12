#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_POSITION = 500;

class TTon{
public:
    TTon ( int pos ) : m_Position( pos )
    { }
    void InsertNeighbour (int neighbour, char ton){
        m_Neighbours.insert( {neighbour, ton} );
    }
    map<int, char>& GetNeighbours(){
        return m_Neighbours;
    }

private:
    int m_Position;
    map<int, char> m_Neighbours;
};

class CKoledy{
public:
    CKoledy( int size, int start, int end ):
                m_Start(start), m_End(end)
    {
        for (int i = 0; i < size; ++i) {
            m_Song.emplace_back( TTon(i) );
        }
    }
    void InsertNeighbour( int position, int neighbour, char ton );
    void GetAllWords ( int startPosition );
    void InsertWordToSong( int position, const string& word, char ton );
private:
    vector<TTon> m_Song;
    map<int, set<string>> m_Words;
    int m_Start;
    int m_End;
};

void CKoledy::InsertNeighbour(int position, int neighbour, char ton) {
    m_Song[position].InsertNeighbour(neighbour, ton);
}

void CKoledy::GetAllWords(int position) {
    if ( position == m_End ){                                               /// IF THE LAST POSITION:
        m_Words.at(m_End).insert("");                                       /// INSERT NOTHING
    }
    for ( const auto& neighbour: m_Song[position].GetNeighbours() ){        /// FOR ALL NEIGHBOURS:
        int neighbourPosition = neighbour.first;
        char neighbourTon = neighbour.second;

        if ( m_Words.find( neighbourPosition ) != m_Words.end() ){          /// IF NEIGHBOUR HAS ALL WORDS:
            for ( const string& word: m_Words.at( neighbourPosition ) )     /// FOR ALL WORDS:
                InsertWordToSong(position, word, neighbourTon);             /// INSERT WORD WITH NEW CHAR IN THIS POSITION
        }
        else {                                                              /// ELSE NEIGHBOUR FIND
            GetAllWords(neighbourPosition);                                 /// ALL HIS NEIGHBOURS WORDS
        }
    }
}

void CKoledy::InsertWordToSong(int position, const string &word, char ton) {
    m_Words.at(position).insert(ton + word);
}

int main(){
    int size, ignoreTon, size_of_neighbours;
    int start, end;

    cin >> size >> ignoreTon;
    cin >> start >> end;

    CKoledy koledy(size, start, end);

    for (int pos = 0; pos < size; ++pos) {
        cin >> size_of_neighbours;

        for (int j = 0; j < size_of_neighbours; ++j) {
            int neighbour; char ton;

            cin >> neighbour >> ton;
            koledy.InsertNeighbour(pos, neighbour, ton);
        }
    }

    return 0;
}
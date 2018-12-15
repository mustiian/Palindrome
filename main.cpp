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
    bool GetAllWords ( int startPosition );
    void InsertWordsToSong( int position, int neiPosition, char ton );
    void InsertWordsToSongReverse( int position, int neiPosition, char ton );
    int  CountAllPalindromes();
private:
    vector<TTon> m_Song;
    map<int, vector<string>> m_Words;
    map<int, vector<string>> m_Words_rev;
    int m_Start;
    int m_End;
};

void CKoledy::InsertNeighbour(int position, int neighbour, char ton) {
    m_Song[position].InsertNeighbour(neighbour, ton);
}

bool CKoledy::GetAllWords(int position) {
    bool gotoEnd = false;

    if ( position == m_End ){                                               /// IF THE LAST POSITION:
        m_Words[m_End].emplace_back("");                                    /// INSERT NOTHING
        m_Words_rev[m_End].emplace_back("");
        return true;
    }

    for ( const auto& neighbour: m_Song[position].GetNeighbours() ){        /// FOR ALL NEIGHBOURS:
        int neighbourPosition = neighbour.first;
        char neighbourTon = neighbour.second;

        if ( m_Words.find( neighbourPosition ) != m_Words.end() ){          /// IF NEIGHBOUR HAS ALL WORDS:
              InsertWordsToSong(position, neighbourPosition, neighbourTon); /// INSERT WORDS WITH NEW CHAR IN THIS POSITION
              InsertWordsToSongReverse(position, neighbourPosition, neighbourTon);
              gotoEnd = true;
        }
        else {                                                              /// ELSE NEIGHBOUR FIND ALL HIS NEIGHBOURS WORDS
            gotoEnd = GetAllWords(neighbourPosition);
            if ( gotoEnd )    {                                              /// IF POSITION GO TO END: INSERT WORDS
                InsertWordsToSong(position, neighbourPosition, neighbourTon);
                InsertWordsToSongReverse(position, neighbourPosition, neighbourTon);
            }
        }
    }
    return gotoEnd;
}

void CKoledy::InsertWordsToSong(int position, int neiPosition, char ton) {
    for ( const string& word: m_Words.at( neiPosition ) ){
        m_Words[position].emplace_back(ton + word);
    }
}

void CKoledy::InsertWordsToSongReverse(int position, int neiPosition, char ton) {
    for ( const string& word: m_Words_rev.at( neiPosition ) ){
        m_Words_rev[position].emplace_back(word + ton);
    }
}

int CKoledy::CountAllPalindromes() {
    int count = 0;

    for (size_t i = 0; i <  m_Words[m_Start].size(); ++i) {
        if ( m_Words[m_Start][i] == m_Words_rev[m_Start][i] ){
            count++;
            count %= 1000000007;
        }
    }

    return count;
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

    koledy.GetAllWords( start );
    cout << koledy.CountAllPalindromes() << endl;
    return 0;
}
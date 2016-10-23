#include "RhymeBot.h"
unordered_map<string, string> syllablesdict;

RhymeBot::RhymeBot(int argc, char *argv[]){
	
	

}



unordered_map<string, string> RhymeBot::parseDictionary(char *argv[1]){
    
	string filename = argv[1];
    ifstream dataFile;
    dataFile.open(filename);
    string line;
    vector<string> words;
    string ans;
    if (!dataFile.is_open()) {
        cout << "Could not open " << filename << "\n";
        exit(0);
    }

    
    
    
    while (!dataFile.eof()) {
        getline(dataFile, line);
        if (line.length() != 0) {
        	if((line.find("(1)") != string::npos) || (line.find("(2)") != string::npos) || (line.find("(3)") != string::npos)){
        		
        		continue;
        	}
            string word = line.substr(0, line.find_first_of(" "));
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            
            string syllable= line.substr(line.find_first_of(" ") + 1);
            transform(syllable.begin(), syllable.end(), syllable.begin(), ::tolower);
            syllable.erase(remove(syllable.begin(),syllable.end(),'0'),syllable.end());
        	syllable.erase(remove(syllable.begin(),syllable.end(),'1'),syllable.end());
        	syllable.erase(remove(syllable.begin(),syllable.end(),'2'),syllable.end());
            syllablesdict[word] = syllable;
            
            
           
        }
    }

    dataFile.close();
    
    return syllablesdict;

}


void RhymeBot::parsePhrases(char *argv[2]){
	string file1 = "saved1.txt";
    ofstream outputStream1(file1, ios::out | ios::binary);
    string file2 = "saved2.txt";
    ofstream outputStream2(file2, ios::out | ios::binary);
    string file3 = "saved3.txt";
    ofstream outputStream3(file3, ios::out | ios::binary);
    string file4 = "saved4.txt";
    ofstream outputStream4(file4, ios::out | ios::binary);
	string filename = argv[2];
    ifstream dataFile;
    dataFile.open(filename);
    string line;
    vector<string> words;
    string ans;
    if (!dataFile.is_open()) {
        cout << "Could not open " << filename << "\n";
        exit(0);
    }
    int x =0;
    
    
    
    while (!dataFile.eof()) {
    	string ans;
        getline(dataFile, line);
        if (line.length() != 0) {
        
        	stringstream stream(line);
        	for(string word; stream>> word;){
        		
        		ans = ans + syllablesdict[word];
            	words.push_back(word);
            }
          	
            reverse(ans.begin(),ans.end());
            ans.erase(remove(ans.begin(),ans.end(),' '),ans.end());
            if( ans[0] >= 'a' && ans[0] <= 'k'){
                outputStream1 << ans +" " +line;
                outputStream1 << endl;
            }
            else if ( ans[0] >='l' && ans[0] <= 'o' ){
                outputStream2 << ans +" " +line;
                outputStream2 << endl;
            }
            else if( ans[0] >= 'p' && ans[0] <= 's'){
                outputStream3 << ans +" " +line;
                outputStream3 << endl;
            }
            else if ( ans[0] >= 't' && ans[0] <= 'z'){
                outputStream4 << ans +" " +line;
                outputStream4 << endl;
            } 

    	}
    	
    }	    	
    outputStream1.close();
    outputStream2.close();
    outputStream3.close();
    outputStream4.close();
}

void RhymeBot::Loadfromfile(char c){
    string word;
    string proncuation;
    string filename1 = "saved1.txt";
    ifstream dataFile1;
    dataFile1.open(filename1);
    string filename2 = "saved2.txt";
    ifstream dataFile2;
    dataFile2.open(filename2);
    string filename3 = "saved3.txt";
    ifstream dataFile3;
    dataFile3.open(filename3);
    string filename4 = "saved4.txt";
    ifstream dataFile4;
    dataFile4.open(filename4);
    string line;
    
    
    if( c >= 'a' && c <= 'k' ){
        while (!dataFile1.eof()) {
            string ans;
            getline(dataFile1, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }
    }
    else if( c >='l' && c <= 'o' ){
        while (!dataFile2.eof()) {
            string ans;
            getline(dataFile2, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if( c >= 'p' && c<= 's'){
        while (!dataFile3.eof()) {
            string ans;
            getline(dataFile3, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }
    }
    else if( c >= 't' && c <= 'z'){
        while (!dataFile4.eof()) {
            string ans;
            getline(dataFile4, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
   
    dataFile1.close();
    dataFile2.close();
    dataFile3.close();
    dataFile4.close();
}

void RhymeBot::TopRhyme(char *argv[]) {

	vector<string> words;
	string s = argv[4];
	string ans;
	string first;
	
	int val = stoi(argv[3]);

	replace(s.begin(),s.end(),'_',' ');
	stringstream stream(s);
    for(string word; stream>> word;){
        ans = ans + syllablesdict[word];	
       		
        words.push_back(word);
    }
    reverse(ans.begin(),ans.end());
    ans.erase(remove(ans.begin(),ans.end(),' '),ans.end());
	trie->startsWith(ans,val);
			
		
}

int main(int argc, char *argv[]){
    string s = argv[4];
    string ans;
    char index;
    vector<string> words;
	clock_t startTime = clock();
    ifstream file("saved1.txt");
	RhymeBot bot(argc,argv);
	bot.parseDictionary(argv);
    if(!file){
        bot.parsePhrases(argv);

    }
    replace(s.begin(),s.end(),'_',' ');
    stringstream stream(s);
    for(string word; stream>> word;){
            
        ans = ans + syllablesdict[word];

        words.push_back(word);
    }       
    reverse(ans.begin(),ans.end());
    ans.erase(remove(ans.begin(),ans.end(),' '),ans.end());

    index = ans[0];
    
    bot.Loadfromfile(index);
	bot.TopRhyme(argv);
	double elapsedTime = (double(clock() - startTime) / CLOCKS_PER_SEC)*1000.0;
	cout << elapsedTime/1000 << " " << "s"<< endl;

	return 0;
}

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
    string file5 = "saved5.txt";
    ofstream outputStream5(file5, ios::out | ios::binary);
    string file6 = "saved6.txt";
    ofstream outputStream6(file6, ios::out | ios::binary);
    string file7 = "saved7.txt";
    ofstream outputStream7(file7, ios::out | ios::binary);
    string file8 = "saved8.txt";
    ofstream outputStream8(file8, ios::out | ios::binary);
    string file9 = "saved9.txt";
    ofstream outputStream9(file9, ios::out | ios::binary);
    string file10= "saved10.txt";
    ofstream outputStream10(file10, ios::out | ios::binary);
    string file11 = "saved11.txt";
    ofstream outputStream11(file11, ios::out | ios::binary);
    string file12 = "saved12.txt";
    ofstream outputStream12(file12, ios::out | ios::binary);
    string file13 = "saved13.txt";
    ofstream outputStream13(file13, ios::out | ios::binary);
    string file14 = "saved14.txt";
    ofstream outputStream14(file14, ios::out | ios::binary);
    string file15 = "saved15.txt";
    ofstream outputStream15(file15, ios::out | ios::binary);
    string file16 = "saved16.txt";
    ofstream outputStream16(file16, ios::out | ios::binary);
    string file17 = "save17.txt";
    ofstream outputStream17(file17, ios::out | ios::binary);
    string file18 = "saved18.txt";
    ofstream outputStream18(file18, ios::out | ios::binary);
    string file19= "saved19.txt";
    ofstream outputStream19(file19, ios::out | ios::binary);
    string file20 = "saved20.txt";
    ofstream outputStream20(file20, ios::out | ios::binary);
    string file21 = "saved21.txt";
    ofstream outputStream21(file21, ios::out | ios::binary);
    string file22 = "saved22.txt";
    ofstream outputStream22(file22, ios::out | ios::binary);
    string file23 = "saved23.txt";
    ofstream outputStream23(file23, ios::out | ios::binary);
    string file24 = "saved24.txt";
    ofstream outputStream24(file24, ios::out | ios::binary);
    string file25 = "saved25.txt";
    ofstream outputStream25(file25, ios::out | ios::binary);
    string file26 = "saved26.txt";
    ofstream outputStream26(file26, ios::out | ios::binary);
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
            if( ans[0] == 'a'){
                outputStream1 << ans +" " +line;
                outputStream1 << endl;
            }
            if ( ans[0] == 'b' ){
                outputStream2 << ans +" " +line;
                outputStream2 << endl;
            }
            if( ans[0]  == 'c'){
                outputStream3 << ans +" " +line;
                outputStream3 << endl;
            }
            if ( ans[0] == 'd'){
                outputStream4 << ans +" " +line;
                outputStream4 << endl;
            } 
            if( ans[0] == 'e' ){
                outputStream5 << ans +" " +line;
                outputStream5 << endl;
            }
            if ( ans[0] =='f'){
                outputStream6 << ans +" " +line;
                outputStream6 << endl;
            }
            if( ans[0] == 'g'){
                outputStream7 << ans +" " +line;
                outputStream7 << endl;
            }
            if ( ans[0] =='h'){
                outputStream8 << ans +" " +line;
                outputStream8 << endl;
            } 
            if( ans[0] =='i'){
                outputStream9 << ans +" " +line;
                outputStream9 << endl;
            }
            if ( ans[0] == 'j'){
                outputStream10 << ans +" " +line;
                outputStream10 << endl;
            }
            if( ans[0] == 'k'){
                outputStream11 << ans +" " +line;
                outputStream11 << endl;
            }
            if ( ans[0] == 'l'){
                outputStream12 << ans +" " +line;
                outputStream12 << endl;
            } 
            if( ans[0] == 'm'){
                outputStream13 << ans +" " +line;
                outputStream13 << endl;
            }
            if ( ans[0] == 'n'){
                outputStream14 << ans +" " +line;
                outputStream14 << endl;
            }
            if( ans[0] == 'o'){
                outputStream15 << ans +" " +line;
                outputStream15 << endl;
            }
            if ( ans[0] == 'p'){
                outputStream16 << ans +" " +line;
                outputStream16 << endl;
            } 
            if( ans[0] == 'q'){
                outputStream17 << ans +" " +line;
                outputStream17 << endl;
            }
            if ( ans[0] == 'r'){
                outputStream18 << ans +" " +line;
                outputStream18 << endl;
            }
            if( ans[0] == 's'){
                outputStream19 << ans +" " +line;
                outputStream19 << endl;
            }
            if ( ans[0] == 't'){
                outputStream20 << ans +" " +line;
                outputStream20 << endl;
            } 
            if( ans[0] == 'u'){
                outputStream21 << ans +" " +line;
                outputStream21 << endl;
            }
            if ( ans[0] == 'v'){
                outputStream22 << ans +" " +line;
                outputStream22 << endl;
            }
            if( ans[0] == 'w'){
                outputStream23 << ans +" " +line;
                outputStream23 << endl;
            }
            if ( ans[0] == 'x'){
                outputStream24 << ans +" " +line;
                outputStream24 << endl;
            }
            if( ans[0] == 'y'){
                outputStream25 << ans +" " +line;
                outputStream25 << endl;
            }
            if ( ans[0] == 'z'){
                outputStream26 << ans +" " +line;
                outputStream26 << endl;
            } 

    	}
    	
    }	    	
    outputStream1.close();
    outputStream2.close();
    outputStream3.close();
    outputStream4.close();
    outputStream5.close();
    outputStream6.close();
    outputStream7.close();
    outputStream8.close(); 
    outputStream9.close();
    outputStream10.close();
    outputStream11.close();
    outputStream12.close();
    outputStream13.close();
    outputStream14.close();
    outputStream15.close();
    outputStream16.close(); 
    outputStream17.close();
    outputStream18.close();
    outputStream19.close();
    outputStream20.close();
    outputStream21.close();
    outputStream22.close();
    outputStream23.close();
    outputStream24.close(); 
    outputStream25.close();
    outputStream26.close(); 
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
    string filename5 = "saved5.txt";
    ifstream dataFile5;
    dataFile5.open(filename5);
    string filename6 = "saved6.txt";
    ifstream dataFile6;
    dataFile6.open(filename6);
    string filename7 = "saved7.txt";
    ifstream dataFile7;
    dataFile7.open(filename7);
    string filename8 = "saved8.txt";
    ifstream dataFile8;
    dataFile8.open(filename8);
    string filename9 = "saved9.txt";
    ifstream dataFile9;
    dataFile9.open(filename9);
    string filename10 = "saved10.txt";
    ifstream dataFile10;
    dataFile10.open(filename10);
    string filename11 = "saved11.txt";
    ifstream dataFile11;
    dataFile11.open(filename11);
    string filename12 = "saved12.txt";
    ifstream dataFile12;
    dataFile12.open(filename12);
    string filename13 = "saved13.txt";
    ifstream dataFile13;
    dataFile13.open(filename13);
    string filename14 = "saved14.txt";
    ifstream dataFile14;
    dataFile14.open(filename14);
    string filename15 = "saved15.txt";
    ifstream dataFile15;
    dataFile15.open(filename15);
    string filename16 = "saved16.txt";
    ifstream dataFile16;
    dataFile16.open(filename16);
    string filename17 = "saved17.txt";
    ifstream dataFile17;
    dataFile17.open(filename17);
    string filename18 = "saved18.txt";
    ifstream dataFile18;
    dataFile18.open(filename18);
    string filename19 = "saved19.txt";
    ifstream dataFile19;
    dataFile19.open(filename19);
    string filename20 = "saved20.txt";
    ifstream dataFile20;
    dataFile20.open(filename20);
    string filename21 = "saved21.txt";
    ifstream dataFile21;
    dataFile21.open(filename21);
    string filename22 = "saved22.txt";
    ifstream dataFile22;
    dataFile22.open(filename22);
    string filename23 = "saved23.txt";
    ifstream dataFile23;
    dataFile23.open(filename23);
    string filename24 = "saved24.txt";
    ifstream dataFile24;
    dataFile24.open(filename24);
    string filename25 = "saved25.txt";
    ifstream dataFile25;
    dataFile25.open(filename25);
    string filename26 = "saved26.txt";
    ifstream dataFile26;
    dataFile26.open(filename26);
 

    string line;
    
    
    if( c  == 'a' ){
        while (!dataFile1.eof()) {
            string ans;
            getline(dataFile1, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }
    }
    else if( c  == 'b'){
        while (!dataFile2.eof()) {
            string ans;
            getline(dataFile2, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if( c == 'c'){
        while (!dataFile3.eof()) {
            string ans;
            getline(dataFile3, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }
    }
    else if( c == 'd'){
        while (!dataFile4.eof()) {
            string ans;
            getline(dataFile4, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if(c == 'e'){
        while (!dataFile5.eof()) {
            string ans;
            getline(dataFile5, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if( c == 'f' ){
        while (!dataFile6.eof()) {
            string ans;
            getline(dataFile6, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }
    }
    else if( c == 'g' ){
        while (!dataFile7.eof()) {
            string ans;
            getline(dataFile7, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if( c == 'h' ){
        while (!dataFile8.eof()) {
            string ans;
            getline(dataFile8, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if( c == 'i' ){
        while (!dataFile9.eof()) {
            string ans;
            getline(dataFile9, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }
    }
    else if( c == 'j' ){
        while (!dataFile10.eof()) {
            string ans;
            getline(dataFile10, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if( c == 'k' ){

        while (!dataFile11.eof()) {
            string ans;
            getline(dataFile11, line);

            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
            
            trie->insert(proncuation,word);
            
        }

    }
    else if( c == 'l'){
        while (!dataFile12.eof()) {
            string ans;
            getline(dataFile12, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }
    }
    else if( c == 'm' ){
        while (!dataFile13.eof()) {
            string ans;
            getline(dataFile13, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if(c == 'n'){
        while (!dataFile14.eof()) {
            string ans;
            getline(dataFile14, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if( c == 'o' ){
        while (!dataFile15.eof()) {
            string ans;
            getline(dataFile15, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }
    }
    else if( c == 'p'){
        while (!dataFile16.eof()) {
            string ans;
            getline(dataFile16, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if( c == 'q' ){
        while (!dataFile17.eof()) {
            string ans;
            getline(dataFile17, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if( c == 'r' ){
        while (!dataFile18.eof()) {
            string ans;
            getline(dataFile18, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }
    }
    else if( c == 's' ){
        while (!dataFile19.eof()) {
            string ans;
            getline(dataFile19, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if( c == 't'){
        while (!dataFile20.eof()) {
            string ans;
            getline(dataFile20, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if( c == 'u'){
        while (!dataFile21.eof()) {
            string ans;
            getline(dataFile21, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }
    }
    else if( c == 'v' ){
        while (!dataFile22.eof()) {
            string ans;
            getline(dataFile22, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if(c == 'w'){
        while (!dataFile23.eof()) {
            string ans;
            getline(dataFile23, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if( c == 'x' ){
        while (!dataFile24.eof()) {
            string ans;
            getline(dataFile24, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }
    }
    else if( c == 'y'){
        while (!dataFile25.eof()) {
            string ans;
            getline(dataFile25, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
    else if(c == 'z' ){
        while (!dataFile26.eof()) {
            string ans;
            getline(dataFile26, line);
            proncuation = line.substr(0, line.find_first_of(" "));
            word = line.substr(line.find_first_of(" ") + 1);
        
            trie->insert(proncuation,word);
            
        }

    }
   


    dataFile1.close();
    dataFile2.close();
    dataFile3.close();
    dataFile4.close();
    dataFile5.close();
    dataFile6.close();
    dataFile7.close();
    dataFile8.close();
    dataFile9.close();
    dataFile10.close();
    dataFile11.close();
    dataFile12.close();
    dataFile13.close();
    dataFile14.close();
    dataFile15.close();
    dataFile16.close();
    dataFile17.close();
    dataFile18.close();
    dataFile19.close();
    dataFile20.close();
    dataFile21.close();
    dataFile22.close();
    dataFile23.close();
    dataFile24.close();
    dataFile25.close();
    dataFile26.close();
    

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
    //clock_t startTime = clock();
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

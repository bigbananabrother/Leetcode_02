class Solution {
public:
    Solution() : m_letter("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") {}
    
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        int key = 0;
        
        key = UrlHashFunc(longUrl);
        AddToPairs(key, longUrl);
        
        return KeyToShortUrl(key);
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return ShortUrlToLongURL(shortUrl);
    }
private:
    int UrlHashFunc(string longUrl)
    {
        // should be unique
        srand (time(NULL));
        return rand();
    }
    bool AddToPairs(int key, string value)
    {
        cout << "key = " << key << endl;
        m_key_value_pairs.push_back(make_pair(key, value));
        return true;
    }
    string KeyToShortUrl(int key)
    {
        int temp_int;
        string temp_str;
        string tiny_url("http://tinyurl.com/");
        for (int a=0; a<6; a++)
        {
            temp_int = key % 62;
            temp_str.insert(0, 1, m_letter[temp_int]);
            key = key / 62;                
        }
        cout << tiny_url + temp_str << endl;
        return tiny_url + temp_str;
    }
    string ShortUrlToLongURL(string shortURL)
    {   
        int key = 0;
        string temp_str;
        vector<pair<int, string>>::iterator begin = m_key_value_pairs.begin();
        vector<pair<int, string>>::iterator end = m_key_value_pairs.end();
        
        
        temp_str = shortURL.substr((shortURL.size()-6), 6);
        for (int a=0; a<6; a++)
        {
            for (int b=0; b<62; b++)
            {
                if (temp_str[a] == m_letter[b])
                {
                    key += b * pow(62, (5-a));
                    break;
                }
            }
        }
        
        
        cout << "key in ShortUrlToLongURL = " << key << endl;
        for(vector<pair<int, string>>::iterator it=begin ; it!=end ; it++)
        {
            if (get<0>(*it) == key)
            {
                return get<1>(*it);
            }
        }
        return "Error";
    }
    const string m_letter;
    vector<pair<int, string>> m_key_value_pairs;
    
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));

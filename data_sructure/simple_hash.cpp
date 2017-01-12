#include <iostream>

#define BIGP 105943
#define COEFF_A 13579
#define COEFF_B 12345

template <typename K, typename V>
struct HashNode {
    K key;
    V value;
    HashNode* next;
    
    HashNode(K new_key, V new_value) {
        this->key = new_key;
        this->value = new_value;
        this->next = NULL;
    }
};

template <typename K>
struct SimpleHashFunc {
    int operator()(const K key, const int map_size) {
        return (key * COEFF_A + COEFF_B) % BIGP % map_size;
    }
};

template <typename K, typename V, typename F>
class HashMap {
    private:
        int map_size;
        int conflicts;
        HashNode<K, V>** map;
        F hash_func;
    
    public:
        HashMap(int new_size) {
            map_size = new_size;
            conflicts = 0;
            map = new HashNode<K, V>* [map_size]();
        }
        
        ~HashMap() {
            for (int i = 0; i < map_size; i++) {
                HashNode<K, V>* node = map[i];
                while (node != NULL) {
                    HashNode<K, V>* old = node;
                    node = node->next;
                    delete old;
                }
                map[i] = NULL;
            }
            
            delete [] map;
        }
        
        void insert(K key, V value) {
            // first calculate hashed value
            int hash_value = hash_func(key, map_size);
            
            if (map[hash_value] == NULL) {
                // new map element
                map[hash_value] = new HashNode<K, V>(key, value);
            } else {
                HashNode<K, V>* node = map[hash_value];
                HashNode<K, V>* prev;
                
                while (node != NULL && node->key != key) {
                    conflicts++;
                    prev = node;
                    node = node->next;
                }
                
                if (node == NULL) {
                    // create a new node
                    prev->next = new HashNode<K, V>(key, value);
                } else {
                    // update current node
                    node->value = value;
                }
            }
        }
        
        bool remove_node(K key) {
            // first calculate hashed value
            int hash_value = hash_func(key, map_size);
            
            // find and remove node
            HashNode<K, V>* node = map[hash_value];
            HashNode<K, V>* prev = NULL;
            
            while (node != NULL) {
                if (node->key == key) {
                    if (prev == NULL) {
                        map[hash_value] = node->next;
                    } else {
                        prev->next = node->next;
                    }
                    delete node;
                    return true;
                }
                prev = node;
                node = node->next;
            }
            
            // can't find node
            return false;
        }
        
        bool get(K key, V& value) {
            // first calculate hashed value
            int hash_value = hash_func(key, map_size);
            
            HashNode<K, V>* node = map[hash_value];
            while (node != NULL) {
                if (node->key == key) {
                    value = node->value;
                    return true;
                }
                node = node->next;
            }
            
            return false;
        }
        
        int get_conflicts() {
            return conflicts;
        }
};

int main() {
    // create a hashmap object
    HashMap<int, int, SimpleHashFunc<int> > map(20);
    map.insert(12345, 1);
    map.insert(38234, 2);
    map.insert(4732, 3);
    map.insert(4134, 4);
    map.insert(128, 5);
    
    std::cout << "total conflicts are " << map.get_conflicts() << std::endl;
    int val;
    if (map.get(38234, val)) {
        std::cout << "value of key 38234 is " << val << std::endl;
    }
    
    map.remove_node(4732);
    if (map.get(4732, val)) {
        std::cout << "key 4732 still here" << std::endl;
    } else {
        std::cout << "key 4732 removed..." << std::endl;
    }
    
    return 0;
}

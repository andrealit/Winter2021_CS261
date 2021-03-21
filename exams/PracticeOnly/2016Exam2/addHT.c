
void addHT(struct HashTable * ht, struct DataElem elem) {
    struct Link* newHashLink;
    struct Link* temp;

    /* step 1. hash index */
    int hashIdx = HASH() & ht->tableSize;

    newHashLink = (struct Link*) malloc (sizeof(struct Link));

    if (ht->table[hashIdx] == 0) {
        ht->table[hashIdx] = newHashLink;
        ht->table[hashIdx]->elem = elem;
    } else {
        temp = ht->table[hashIdx];

        while(temp != NULL) {

            if (strcmp(temp->elem->TYPE_KEY, elem->TYPE_KEY)) {
                temp->elem->TYPE_VALUE = elem->TYPE_VALUE;
            } else {
                temp = temp->next;
            }
        }

        /* fill values */
        newHashLink->elem = elem;

        newHashLink->next = ht->table[hashIdx];

        ht->table[hashIdx] = newHashLink;
    }

    ht->count++;
}
#include "graph.h"

void
Graph::computeRanks(Ranks *ranks)
{
    const qreal d = 0.8;
    const int numloops = 10;
    const int npages = this->size();

    iterator it;
    for (it = this->begin(); it != this->end(); ++it)
        ranks->insert(it.key(), qreal(1.0 / npages));

    for (int i = 0; i < numloops; i++) {
        Ranks newranks;
        //iterator page;
        for (const_iterator page = this->begin(); page != this->end(); ++page) {
            qreal newrank = qreal((1 - d) / npages);
            foreach (const QUrl &node, page.value()) {
                if (this->value(node).contains(page.key())) {
                    newrank = newrank + d * (ranks->value(node) / this->value(node).size());
                }
            }
            newranks.insert(page.key(), newrank);
        }
        newranks.swap(*ranks);
    }
}

#include "GFimg.h"

int main(int argc, char *argv[]) {

    GFimg *m_pGF = new GFimg(_tiff.toStdString(), 0, _xml.toStdString(),_rpb.toStdString());
    m_pGF->getCorner();
    m_pGF->init();
    m_pGF->caldensity();
    m_pGF->writeDen(sdir.toStdString());
    delete m_pGF; m_pGF=NULL;
}

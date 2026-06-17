#pragma HALFEDGE

class HalfEdge {
public:
  HalfEdge();  
  ~HalfEdge();

  HalfEdge(const HalfEdge& h);  
  HalfEdge operator=(const HalfEdge& h);  

  HalfEdge(HalfEdge&& h);
  HalfEdge operator=(HalfEdge&& h);  
private:
    
};
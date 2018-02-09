## Evonet

this project runs an evolution simulator that
- environment
  - generated from a pixel image
  - contains food, varying in color
  - contains natural hazards
  - changes over time
- creatures
  - have body color for species identification
  - have food color preference
  - controlled by neural networks
  - size (more energy stored, required)
  - has sensors
    - color vision
      - can distinguish between the ground and other creatures
  - can take actions
    - eat (+++energy)
      - creatures are either carnivorous or herbivorous
    - move (-energy)
    - attack (--energy, drops meat if creature dies)
    - reproduce (---energy)
  

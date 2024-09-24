
extern void pcem_close(void);
extern void pcemglue_hsync(void);

uint8_t keyboard_at_read(uint16_t port, void *priv);
uint8_t mem_read_romext(uint32_t addr, void *priv);
uint16_t mem_read_romextw(uint32_t addr, void *priv);
uint32_t mem_read_romextl(uint32_t addr, void *priv);
void pcem_linear_mark(int offset);

extern int SOUNDBUFLEN;

extern void *pcem_mapping_linear_priv;
extern uae_u32 pcem_mapping_linear_offset;
extern uint8_t(*pcem_linear_read_b)(uint32_t addr, void* priv);
extern uint16_t(*pcem_linear_read_w)(uint32_t addr, void* priv);
extern uint32_t(*pcem_linear_read_l)(uint32_t addr, void* priv);
extern void (*pcem_linear_write_b)(uint32_t addr, uint8_t  val, void* priv);
extern void (*pcem_linear_write_w)(uint32_t addr, uint16_t val, void* priv);
extern void (*pcem_linear_write_l)(uint32_t addr, uint32_t val, void* priv);

void initpcemvideo(void *p, bool swapped);
uae_u8 pcem_read_io(int, int);
uae_u8 *getpcembuffer32(int x, int y, int yy);
void put_pci_pcem(uaecptr addr, uae_u8 v);
uae_u8 get_pci_pcem(uaecptr addr);
void put_mem_pcem(uaecptr addr, uae_u32 v, int size);
uae_u32 get_mem_pcem(uaecptr addr, int size);
void mca_add(uint8_t(*read)(int addr, void *priv), void (*write)(int addr, uint8_t val, void *priv), void (*reset)(void *priv), void *priv);
void put_io_pcem(uaecptr addr, uae_u32 v, int size);
uae_u32 get_io_pcem(uaecptr addr, int size);
void io_sethandlerx(uint16_t base, int size,
		    uint8_t(*inb)(uint16_t addr, void *priv),
		    uint16_t(*inw)(uint16_t addr, void *priv),
		    uint32_t(*inl)(uint16_t addr, void *priv),
		    void (*outb)(uint16_t addr, uint8_t  val, void *priv),
		    void (*outw)(uint16_t addr, uint16_t val, void *priv),
		    void (*outl)(uint16_t addr, uint32_t val, void *priv),
		    void *priv);
void io_removehandlerx(uint16_t base, int size,
		       uint8_t(*inb)(uint16_t addr, void *priv),
		       uint16_t(*inw)(uint16_t addr, void *priv),
		       uint32_t(*inl)(uint16_t addr, void *priv),
		       void (*outb)(uint16_t addr, uint8_t  val, void *priv),
		       void (*outw)(uint16_t addr, uint16_t val, void *priv),
		       void (*outl)(uint16_t addr, uint32_t val, void *priv),
		       void *priv);
void upc_set_mouse(void (*mouse_write)(uint8_t, void*), void *p);
void pcemvideorbswap(bool swapped);

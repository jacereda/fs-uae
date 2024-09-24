
void casablanca_map_overlay(void);
void draco_map_overlay(void);
void draco_init(void);
void draco_free(void);
bool draco_mouse(int port, int x, int y, int z, int b);
void draco_bustimeout(uaecptr addr);
void draco_ext_interrupt(bool);
void draco_keycode(uae_u16 scancode, uae_u8 state);
void draco_serial_init(void **s1, void **s2);
void draco_svga_irq(bool);
void draco_kdb_queue_add(void *d, uint8_t val, int state);
uint8_t draco_1wire_crc8(uint8_t *addr, uint8_t len);
void draco_set_scsi_irq(int id, int level);
int draco_kbc_translate(uint8_t val);
int draco_keyboard_get_rate(void);
void *draco_keyboard_init(void);
void keyboard_at_write(uint8_t val, void *priv);
void draco_key_process(uint16_t scan, int down);

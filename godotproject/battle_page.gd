extends Node2D

const Character = preload("res://character.tscn")

var rng = RandomNumberGenerator.new()

var ours = []
var theirs = []

var hitline = false
var hitline_from = Vector2(0, 0)
var hitline_to = Vector2(0, 0)

func makechar(slot: int, is_ours: bool):
	var pos = Vector2i(400, 220)
	if is_ours:
		pos = Vector2i(405, 416)
	
	if slot > 4:
		pos += Vector2i(122 * (slot - 5) + (52 if is_ours else 66), (1 if is_ours else -1) * 135)
	else:
		pos += Vector2i(122 * (slot - 1), 0)
		
	var ch = Character.instantiate()
	ch.position = pos
	ch.atk = randi_range(1, 5)
	ch.hp = randi_range(1, 5)
	ch.set_z_index(-1)
	add_child(ch)
	return ch
	
func doattack(src: Character, dest: Character):
	hitline = true
	hitline_from = src.position
	hitline_to = dest.position
	await get_tree().create_timer(1).timeout
	hitline = false
	src.hp -= dest.atk
	dest.hp -= src.atk
	if src.hp <= 0:
		ours[ours.find(src)] = null
		remove_child(src)
	if dest.hp <= 0:
		theirs[theirs.find(dest)] = null
		remove_child(dest)
	queue_redraw()

func _draw():
	if hitline:
		var offset = Vector2(128.0 / 2, 192.0 / 2)
		draw_line(hitline_from + offset, hitline_to + offset, Color.RED, 10)

# Called when the node enters the scene tree for the first time.
func _ready():
	for i in range(1,8):
		ours.push_back(makechar(i, true))
		theirs.push_back(makechar(i, false))
	
	for i in range(1,1000):
		var from = rng.randi_range(0, 6)
		var to = rng.randi_range(0, 6)
		var src = ours[from]
		var dest = theirs[to]
		if src != null and dest != null:
			await doattack(src, dest)
	
	print('fight done')
	

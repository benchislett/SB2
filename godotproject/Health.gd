extends Label

func _on_character_newhp(newvalue):
	self.text = str(newvalue)

func _ready():
	self.text = str(self.get_parent().hp)

extends Label

func _on_character_newatk(newvalue):
	self.text = str(newvalue)

func _ready():
	self.text = str(self.get_parent().atk)

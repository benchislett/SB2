class_name Character

extends Node2D

signal newhp(newvalue: int)
var hp = 1:
	get:
		return hp
	set(newvalue):
		hp = newvalue
		newhp.emit(hp)

signal newatk(newvalue: int)
var atk = 1:
	get:
		return atk
	set(newvalue):
		atk = newvalue
		newatk.emit(atk)

var id = "test_name"

func _ready():
	pass


# Generated by Django 2.2.24 on 2021-09-05 13:44

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('rooms', '0004_auto_20210901_2355'),
    ]

    operations = [
        migrations.RenameField(
            model_name='room',
            old_name='instatant_book',
            new_name='instant_book',
        ),
    ]
